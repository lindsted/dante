/*
 * Copyright (c) 1997, 1998, 1999, 2000, 2001, 2003, 2005, 2006, 2008, 2009,
 *               2010
 *      Inferno Nettverk A/S, Norway.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. The above copyright notice, this list of conditions and the following
 *    disclaimer must appear in all copies of the software, derivative works
 *    or modified versions, and any portions thereof, aswell as in all
 *    supporting documentation.
 * 2. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by
 *      Inferno Nettverk A/S, Norway.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Inferno Nettverk A/S requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  sdc@inet.no
 *  Inferno Nettverk A/S
 *  Oslo Research Park
 *  Gaustadalléen 21
 *  NO-0349 Oslo
 *  Norway
 *
 * any improvements or extensions that they make and grant Inferno Nettverk A/S
 * the rights to redistribute these changes.
 *
 */

#include "common.h"
#include "config_parse.h"

static const char rcsid[] =
"$Id: tostring.c,v 1.57.2.2 2010/05/24 16:38:36 karls Exp $";

char *
proxyprotocols2string(proxyprotocols, str, strsize)
   const struct proxyprotocol_t *proxyprotocols;
   char *str;
   size_t strsize;
{
   size_t strused;

   if (strsize == 0) {
      static char buf[256];

      str = buf;
      strsize = sizeof(buf);
   }

   *str    = NUL;
   strused = 0;

   if (proxyprotocols->socks_v4)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE(PROXY_SOCKS_V4s));

   if (proxyprotocols->socks_v5)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE(PROXY_SOCKS_V5s));

   if (proxyprotocols->msproxy_v2)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE(PROXY_MSPROXY_V2s));

   if (proxyprotocols->http_v1_0)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE(PROXY_HTTP_V1_0s));

   if (proxyprotocols->upnp)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE(PROXY_UPNPs));

   if (proxyprotocols->direct)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE(PROXY_DIRECTs));

   STRIPTRAILING(str, strused);
   return str;
}

char *
protocols2string(protocols, str, strsize)
   const struct protocol_t *protocols;
   char *str;
   size_t strsize;
{
   size_t strused;

   if (strsize == 0) {
      static char buf[16];

      str = buf;
      strsize = sizeof(buf);
   }

   *str    = NUL;
   strused = 0;

   if (protocols->tcp)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE(PROTOCOL_TCPs));

   if (protocols->udp)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE(PROTOCOL_UDPs));

   STRIPTRAILING(str, strused);
   return str;
}

const char *
socks_packet2string(packet, type)
     const void *packet;
     int type;
{
   static char buf[1024];
   char hstring[MAXSOCKSHOSTSTRING];
   unsigned char version;
   const struct request_t *request = NULL;
   const struct response_t *response = NULL;

   switch (type) {
      case SOCKS_REQUEST:
         request = (const struct request_t *)packet;
         version = request->version;
         break;

      case SOCKS_RESPONSE:
         response = (const struct response_t *)packet;
         version   = response->version;
         break;

     default:
       SERRX(type);
  }

   switch (version) {
      case PROXY_SOCKS_V4:
      case PROXY_SOCKS_V4REPLY_VERSION:
         switch (type) {
            case SOCKS_REQUEST:
               snprintfn(buf, sizeof(buf),
               "(V4) VN: %d CD: %d address: %s",
               request->version, request->command,
               sockshost2string(&request->host, hstring, sizeof(hstring)));
               break;

            case SOCKS_RESPONSE:
               snprintfn(buf, sizeof(buf), "(V4) VN: %d CD: %d address: %s",
               response->version, response->reply,
               sockshost2string(&response->host, hstring, sizeof(hstring)));
               break;
         }
         break;

      case PROXY_SOCKS_V5:
         switch (type) {
            case SOCKS_REQUEST:
               snprintfn(buf, sizeof(buf),
               "VER: %d CMD: %d FLAG: %d ATYP: %d address: %s",
               request->version, request->command, request->flag,
               request->host.atype,
               sockshost2string(&request->host, hstring, sizeof(hstring)));
               break;

            case SOCKS_RESPONSE:
               snprintfn(buf, sizeof(buf),
               "VER: %d REP: %d FLAG: %d ATYP: %d address: %s",
               response->version, response->reply, response->flag,
               response->host.atype,
               sockshost2string(&response->host, hstring, sizeof(hstring)));
               break;
         }
         break;

      default:
         SERRX(version);
  }

   return buf;
}

enum operator_t
string2operator(string)
   const char *string;
{

   if (strcmp(string, "eq") == 0 || strcmp(string, "=") == 0)
      return eq;

   if (strcmp(string, "ne") == 0 || strcmp(string, "!=") == 0)
      return neq;

   if (strcmp(string, "ge") == 0 || strcmp(string, ">=") == 0)
      return ge;

   if (strcmp(string, "le") == 0 || strcmp(string, "<=") == 0)
      return le;

   if (strcmp(string, "gt") == 0 || strcmp(string, ">") == 0)
      return gt;

   if (strcmp(string, "lt") == 0 || strcmp(string, "<") == 0)
      return lt;

   /* parser should make sure this never happens. */
   SERRX(string);

   /* NOTREACHED */
}

const char *
operator2string(operator)
   enum operator_t operator;
{

   switch (operator) {
      case none:
         return QUOTE("none");

      case eq:
         return QUOTE("eq");

      case neq:
         return QUOTE("neq");

      case ge:
         return QUOTE("ge");

      case le:
         return QUOTE("le");

      case gt:
         return QUOTE("gt");

      case lt:
         return QUOTE("lt");

      case range:
         return QUOTE("range");

      default:
         SERRX(operator);
   }

   /* NOTREACHED */
}

const char *
ruleaddr2string(address, string, len)
   const struct ruleaddr_t *address;
   char *string;
   size_t len;
{
   size_t lenused;

   if (string == NULL || len == 0) {
      static char addrstring[MAXRULEADDRSTRING];

      string = addrstring;
      len    = sizeof(addrstring);
   }

   lenused = snprintf(string, len, "%s ", atype2string(address->atype));

   switch (address->atype) {
      case SOCKS_ADDR_IPV4: {
         char *a;

         snprintfn(&string[lenused], len - lenused,
         "%s/%d%s, %s: %s%d%s, %s: %s%d%s, %s: %s, %s: %s%d",
         strcheck(a = strdup(inet_ntoa(address->addr.ipv4.ip))),
         bitcount((unsigned long)address->addr.ipv4.mask.s_addr),
         QUOTE0(),
         QUOTE("tcp"),
         QUOTE0(),
         ntohs(address->port.tcp),
         QUOTE0(),
         QUOTE("udp"),
         QUOTE0(),
         ntohs(address->port.udp),
         QUOTE0(),
         QUOTE("op"),
         operator2string(address->operator),
         QUOTE("end"),
         QUOTE0(),
         ntohs(address->portend));

         free(a);
         break;
      }

      case SOCKS_ADDR_DOMAIN:
         snprintfn(&string[lenused], len - lenused,
         "%s%s, %s: %s%d%s, %s: %s%d%s, %s: %s, %s: %s%d",
         address->addr.domain,
         QUOTE0(),
         QUOTE("tcp"),
         QUOTE0(),
         ntohs(address->port.tcp),
         QUOTE0(),
         QUOTE("udp"),
         QUOTE0(),
         ntohs(address->port.udp),
         QUOTE0(),
         QUOTE("op"),
         operator2string(address->operator),
         QUOTE("end"),
         QUOTE0(),
         ntohs(address->portend));
         break;

      case SOCKS_ADDR_IFNAME:
         snprintfn(&string[lenused], len - lenused,
         "%s%s, %s: %s%d%s, %s : %s%d%s, %s: %s, %s: %s%d",
         address->addr.ifname,
         QUOTE0(),
         QUOTE("tcp"),
         QUOTE0(),
         ntohs(address->port.tcp),
         QUOTE0(),
         QUOTE("udp"),
         QUOTE0(),
         ntohs(address->port.udp),
         QUOTE0(),
         QUOTE("op"),
         operator2string(address->operator),
         QUOTE("end"),
         QUOTE0(),
         ntohs(address->portend));
         break;

      default:
         SERRX(address->atype);
   }

   return string;
}

const char *
protocol2string(protocol)
   int protocol;
{

   switch (protocol) {
      case SOCKS_TCP:
         return QUOTE(PROTOCOL_TCPs);

      case SOCKS_UDP:
         return QUOTE(PROTOCOL_UDPs);

      default:
         SERRX(protocol);
   }

   /* NOTREACHED */
}

const char *
resolveprotocol2string(resolveprotocol)
   int resolveprotocol;
{
   switch (resolveprotocol) {
      case RESOLVEPROTOCOL_TCP:
         return QUOTE(PROTOCOL_TCPs);

      case RESOLVEPROTOCOL_UDP:
         return QUOTE(PROTOCOL_UDPs);

      case RESOLVEPROTOCOL_FAKE:
         return QUOTE("fake");

      default:
         SERRX(resolveprotocol);
   }

   /* NOTREACHED */
}

const char *
command2string(command)
   int command;
{

   switch (command) {
      case SOCKS_BIND:
         return QUOTE(SOCKS_BINDs);

      case SOCKS_CONNECT:
         return QUOTE(SOCKS_CONNECTs);

      case SOCKS_UDPASSOCIATE:
         return QUOTE(SOCKS_UDPASSOCIATEs);

      /* pseudo commands. */
      case SOCKS_ACCEPT:
         return QUOTE(SOCKS_ACCEPTs);

      case SOCKS_BINDREPLY:
         return QUOTE(SOCKS_BINDREPLYs);

      case SOCKS_UDPREPLY:
         return QUOTE(SOCKS_UDPREPLYs);

      case SOCKS_DISCONNECT:
         return QUOTE(SOCKS_DISCONNECTs);

      case SOCKS_UNKNOWN:
         return QUOTE(SOCKS_UNKNOWNs);

      default:
         SERRX(command);
   }

   /* NOTREACHED */
}

char *
commands2string(command, str, strsize)
   const struct command_t *command;
   char *str;
   size_t strsize;
{
   size_t strused;

   if (strsize == 0) {
      static char buf[128];

      str = buf;
      strsize = sizeof(buf);
   }

   *str    = NUL;
   strused = 0;

   if (command->bind)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      command2string(SOCKS_BIND));

   if (command->bindreply)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      command2string(SOCKS_BINDREPLY));

   if (command->connect)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      command2string(SOCKS_CONNECT));

   if (command->udpassociate)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      command2string(SOCKS_UDPASSOCIATE));

   if (command->udpreply)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      command2string(SOCKS_UDPREPLY));

   STRIPTRAILING(str, strused);
   return str;
}

const char *
method2string(method)
   int method;
{

   switch (method) {
      case AUTHMETHOD_NOTSET:
         return QUOTE(AUTHMETHOD_NOTSETs);

      case AUTHMETHOD_NONE:
         return QUOTE(AUTHMETHOD_NONEs);

      case AUTHMETHOD_GSSAPI:
         return QUOTE(AUTHMETHOD_GSSAPIs);

      case AUTHMETHOD_UNAME:
         return QUOTE(AUTHMETHOD_UNAMEs);

      case AUTHMETHOD_NOACCEPT:
         return QUOTE(AUTHMETHOD_NOACCEPTs);

      case AUTHMETHOD_RFC931:
         return QUOTE(AUTHMETHOD_RFC931s);

      case AUTHMETHOD_PAM:
         return QUOTE(AUTHMETHOD_PAMs);

      default:
         SERRX(method);
   }

   /* NOTREACHED */
}

const char *
version2string(version)
   int version;
{

   switch (version) {
      case PROXY_SOCKS_V4:
         return QUOTE(PROXY_SOCKS_V4s);

      case PROXY_SOCKS_V5:
         return QUOTE(PROXY_SOCKS_V5s);

      case PROXY_MSPROXY_V2:
         return QUOTE(PROXY_MSPROXY_V2s);

      case PROXY_HTTP_V1_0:
         return QUOTE(PROXY_HTTP_V1_0s);

      case PROXY_UPNP:
         return QUOTE(PROXY_UPNPs);

      case PROXY_DIRECT:
         return QUOTE(PROXY_DIRECTs);

      default:
         SERRX(version);
   }

   /* NOTREACHED */
}

char *
methods2string(methodc, methodv, str, strsize)
   size_t methodc;
   const int methodv[];
   char *str;
   size_t strsize;
{
   size_t strused;
   size_t i;

   if (strsize == 0) {
      static char buf[512];

      str = buf;
      strsize = sizeof(buf);
   }

   *str    = NUL;
   strused = 0;

   strused = 0;
   for (i = 0; i < methodc; ++i)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      method2string(methodv[i]));

   STRIPTRAILING(str, strused);
   return str;
}

int
string2method(methodname)
   const char *methodname;
{
   struct {
      char   *methodname;
      int    method;
   } method[] = {
      { AUTHMETHOD_NONEs,     AUTHMETHOD_NONE     },
      { AUTHMETHOD_UNAMEs,    AUTHMETHOD_UNAME    },
      { AUTHMETHOD_GSSAPIs,   AUTHMETHOD_GSSAPI   },
      { AUTHMETHOD_RFC931s,   AUTHMETHOD_RFC931   },
      { AUTHMETHOD_PAMs,      AUTHMETHOD_PAM      }
   };
   size_t i;

   for (i = 0; i < ELEMENTS(method); ++i)
      if (strcmp(method[i].methodname, methodname) == 0)
         return method[i].method;

   return -1;
}

char *
sockshost2string(host, string, len)
   const struct sockshost_t *host;
   char *string;
   size_t len;
{

   if (string == NULL || len == 0) {
      static char hstring[MAXSOCKSHOSTSTRING];

      string = hstring;
      len    = sizeof(hstring);
   }

   switch (host->atype) {
      case SOCKS_ADDR_IPV4:
         snprintfn(string, len, "%s.%d",
         inet_ntoa(host->addr.ipv4), ntohs(host->port));
         break;

      case SOCKS_ADDR_IPV6:
            snprintfn(string, len, "%s.%d",
            "<IPv6 address not supported>", ntohs(host->port));
            break;

      case SOCKS_ADDR_DOMAIN:
         snprintfn(string, len, "%s.%d", host->addr.domain, ntohs(host->port));
         break;

      default:
         SERRX(host->atype);
   }

   return string;
}

char *
gwaddr2string(gw, string, len)
   const gwaddr_t *gw;
   char *string;
   size_t len;
{

   if (string == NULL || len == 0) {
      static char hstring[MAXSOCKSHOSTSTRING];

      string = hstring;
      len    = sizeof(hstring);
   }

   switch (gw->atype) {
      case SOCKS_ADDR_IPV4:
         snprintfn(string, len, "%s.%d",
         inet_ntoa(gw->addr.ipv4), ntohs(gw->port));
         break;

      case SOCKS_ADDR_DOMAIN:
         snprintfn(string, len, "%s.%d", gw->addr.domain, ntohs(gw->port));
         break;

      case SOCKS_ADDR_IFNAME:
         snprintfn(string, len, "%s", gw->addr.ifname);
         break;

      case SOCKS_ADDR_URL:
         snprintfn(string, len, "%s", gw->addr.urlname);
         break;

      default:
         SERRX(gw->atype);
   }

   return string;
}

char *
sockaddr2string(address, string, len)
   const struct sockaddr *address;
   char *string;
   size_t len;
{

   if (string == NULL || len == 0) {
      static char addrstring[MAXSOCKADDRSTRING];

      string = addrstring;
      len    = sizeof(addrstring);
   }

   switch (address->sa_family) {
      case AF_UNIX: {
         /* LINTED pointer casts may be troublesome */
         const struct sockaddr_un *addr = (const struct sockaddr_un *)address;

         strncpy(string, addr->sun_path, len - 1);
         string[len - 1] = NUL;
         break;
      }

      case AF_INET: {
         /* LINTED pointer casts may be troublesome */
         const struct sockaddr_in *addr = TOCIN(address);

         snprintfn(string, len, "%s.%d",
         inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));
         break;
      }

      default:
         snprintfn(string, len, "<unknown af %d>", address->sa_family);
   }

   return string;
}

struct udpheader_t *
string2udpheader(data, len, header)
   const char *data;
   size_t len;
   struct udpheader_t *header;
{

   bzero(header, sizeof(*header));

   if (len < sizeof(header->flag))
      return NULL;
   memcpy(&header->flag, data, sizeof(header->flag));
   data += sizeof(header->flag);
   len -= sizeof(header->flag);

   if (len < sizeof(header->frag))
      return NULL;
   memcpy(&header->frag, data, sizeof(header->frag));
   data += sizeof(header->frag);
   len -= sizeof(header->frag);

   if (mem2sockshost(&header->host, (const unsigned char *)data, len,
   PROXY_SOCKS_V5) == NULL)
      return NULL;

   return header;
}

char *
extensions2string(extensions, str, strsize)
   const struct extension_t *extensions;
   char *str;
   size_t strsize;
{
   size_t strused;

   if (strsize == 0) {
      static char buf[16];

      str = buf;
      strsize = sizeof(buf);
   }

   *str    = NUL;
   strused = 0;

   if (extensions->bind)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE("bind"));

   STRIPTRAILING(str, strused);
   return str;
}

char *
str2upper(string)
   char *string;
{

   while (*string != NUL) {
      *string = toupper(*string);
      ++string;
   }

   return string;
}

char *
socket2string(s, buf, buflen)
   const int s;
   char *buf;
   size_t buflen;
{
   struct sockaddr addr;
   socklen_t len;
   char src[MAXSOCKADDRSTRING], dst[MAXSOCKADDRSTRING], *protocol;
   int val;

   if (buflen == 0) {
      static char sbuf[256];

      buf    = sbuf;
      buflen = sizeof(sbuf);
   }

   *buf = NUL;

   len = sizeof(addr);
   if (getsockname(s, &addr, &len) == -1)
      return buf;

   sockaddr2string(&addr, src, sizeof(src));

   len = sizeof(addr);
   if (getpeername(s, &addr, &len) == -1)
      return buf;

   sockaddr2string(&addr, dst, sizeof(dst));

   len = sizeof(val);
   if (getsockopt(s, SOL_SOCKET, SO_TYPE, &val, &len) != 0)
      return buf;

   switch (val) {
      case SOCK_DGRAM:
         protocol = PROTOCOL_UDPs;
         break;

      case SOCK_STREAM:
         protocol = PROTOCOL_TCPs;
         break;

      default:
         protocol = "unknown";
   }

   snprintf(buf, buflen, "laddr: %s, raddr: %s, protocol: %s",
   src, dst, protocol);

   return buf;
}

const char *
atype2string(atype)
   const int atype;
{

   switch (atype) {
      case SOCKS_ADDR_IPV4:
         return "IPv4 address";

      case SOCKS_ADDR_IFNAME:
         return "interface name";

      case SOCKS_ADDR_DOMAIN:
         return "host/domain name";

      case SOCKS_ADDR_IPV6:
         return "IPv6 address";

      case SOCKS_ADDR_URL:
         return "url string";

      default:
         SERRX(atype);
   }

   /* NOTREACHED */
}

#if HAVE_GSSAPI
const char *
gssapiprotection2string(protection)
   const int protection;
{
   switch (protection) {
      case SOCKS_GSSAPI_CLEAR:
         return "clear";

      case SOCKS_GSSAPI_INTEGRITY:
         return "integrity";

      case SOCKS_GSSAPI_CONFIDENTIALITY:
         return "confidentiality";

      case SOCKS_GSSAPI_PERMESSAGE:
         return "per-message";
   }

   return "unknown gssapi protection";
}
#endif /* HAVE_GSSAPI */

#if !SOCKS_CLIENT

char *
logtypes2string(logtypes, str, strsize)
   const struct logtype_t *logtypes;
   char *str;
   size_t strsize;
{
   size_t strused;
   size_t i;

   if (strsize == 0) {
      static char buf[512];

      str = buf;
      strsize = sizeof(buf);
   }

   *str    = NUL;
   strused = 0;

   if (logtypes->type & LOGTYPE_SYSLOG)
      strused += snprintfn(&str[strused], strsize - strused, "\"syslog.%s\", ",
      logtypes->facilityname);

   if (logtypes->type & LOGTYPE_FILE)
      for (i = 0; i < logtypes->fpc; ++i)
         strused += snprintfn(&str[strused], strsize - strused, "\"%s\", ",
         logtypes->fnamev[i]);

   STRIPTRAILING(str, strused);
   return str;
}

char *
options2string(options, prefix, str, strsize)
   const struct option_t *options;
   const char *prefix;
   char *str;
   size_t strsize;
{
   size_t strused;

   if (strsize == 0) {
      static char buf[1024];

      str = buf;
      strsize = sizeof(buf);
   }

   *str    = NUL;
   strused = 0;

   strused += snprintfn(&str[strused], strsize - strused,
   "\"%sconfigfile\": \"%s\",\n", prefix, options->configfile == NULL ?
   SOCKD_CONFIGFILE : options->configfile);

   strused += snprintfn(&str[strused], strsize - strused,
   "\"%sdaemon\": \"%d\",\n", prefix, options->daemon);

   strused += snprintfn(&str[strused], strsize - strused,
   "\"%sdebug\": \"%d\",\n", prefix, options->debug);

   strused += snprintfn(&str[strused], strsize - strused,
   "\"%skeepalive\": \"%d\",\n", prefix, options->keepalive);

   strused += snprintfn(&str[strused], strsize - strused,
   "\"%slinebuffer\": \"%d\",\n", prefix, options->debug);

   strused += snprintfn(&str[strused], strsize - strused,
   "\"%sservercount\": \"%lu\",\n", prefix, (unsigned long)options->serverc);

   STRIPTRAILING(str, strused);
   return str;
}

char *
logs2string(logs, str, strsize)
   const struct log_t *logs;
   char *str;
   size_t strsize;
{
   size_t strused;

   if (strsize == 0) {
      static char buf[128];

      str = buf;
      strsize = sizeof(buf);
   }

   *str    = NUL;
   strused = 0;

   if (logs->connect)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE(SOCKS_LOG_CONNECTs));

   if (logs->disconnect)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE(SOCKS_LOG_DISCONNECTs));

   if (logs->data)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE(SOCKS_LOG_DATAs));

   if (logs->error)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE(SOCKS_LOG_ERRORs));

   if (logs->iooperation)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE(SOCKS_LOG_IOOPERATIONs));

   STRIPTRAILING(str, strused);
   return str;
}

const char *
childtype2string(type)
   int type;
{

   switch (type) {
      case CHILD_IO:
         return "io";

      case CHILD_MOTHER:
         return "mother";

      case CHILD_NEGOTIATE:
         return "negotiator";

      case CHILD_REQUEST:
         return "request";

      default:
         SERRX(type);
   }

   /* NOTREACHED */
}

const char *
verdict2string(verdict)
   int verdict;
{

   return verdict == VERDICT_PASS ?
   QUOTE(VERDICT_PASSs) : QUOTE(VERDICT_BLOCKs);
}

char *
list2string(list, str, strsize)
   const struct linkedname_t *list;
   char *str;
   size_t strsize;
{
   size_t strused;

   if (strsize)
      *str = NUL; /* make sure we return a NUL terminated string. */
   else
      return str;

   strused = 0;

   for (; list != NULL; list = list->next)
      strused += snprintfn(&str[strused], strsize - strused, "\"%s\", ",
      list->name);

   return str;
}

char *
compats2string(compats, str, strsize)
   const struct compat_t *compats;
   char *str;
   size_t strsize;
{
   size_t strused;

   if (strsize == 0) {
      static char buf[32];

      str = buf;
      strsize = sizeof(buf);
   }

   *str    = NUL;
   strused = 0;

   if (compats->reuseaddr)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE("reuseaddr"));

   if (compats->sameport)
      strused += snprintfn(&str[strused], strsize - strused, "%s, ",
      QUOTE("sameport"));

   STRIPTRAILING(str, strused);
   return str;
}

char *
srchosts2string(srchost, prefix, str, strsize)
   const struct srchost_t *srchost;
   const char *prefix;
   char *str;
   size_t strsize;
{
   size_t strused;

   if (strsize == 0) {
      static char buf[32];

      str = buf;
      strsize = sizeof(buf);
   }

   *str    = NUL;
   strused = 0;

   if (srchost->nomismatch)
      strused += snprintfn(&str[strused], strsize - strused,
      "\"%snomismatch\", ", prefix);

   if (srchost->nounknown)
      strused += snprintfn(&str[strused], strsize - strused,
      "\"%snounknown\",", prefix);

   STRIPTRAILING(str, strused);
   return str;
}

const char *
uid2name(uid)
   uid_t uid;
{
   struct passwd *pw;

   if ((pw = getpwuid(uid)) == NULL)
      return NULL;

   return pw->pw_name;
}

char *
timeouts2string(timeouts, prefix, str, strsize)
   const struct timeout_t *timeouts;
   const char *prefix;
   char *str;
   size_t strsize;
{
   size_t strused;

   if (strsize == 0) {
      static char buf[64];

      str = buf;
      strsize = sizeof(buf);
   }

   *str    = NUL;
   strused = 0;

   strused += snprintfn(&str[strused], strsize - strused,
   "\"%sconnecttimeout\": \"%ld\",\n", prefix, (long)timeouts->negotiate);

   strused += snprintfn(&str[strused], strsize - strused,
   "\"%siotimeout\": tcp: \"%lu\", udp: \"%lu\" \n",
   prefix, (unsigned long)timeouts->tcpio, (unsigned long)timeouts->udpio);

   STRIPTRAILING(str, strused);
   return str;
}

const char *
rotation2string(rotation)
   int rotation;
{

   switch (rotation) {
      case ROTATION_NONE:
         return "none";

      case ROTATION_ROUTE:
         return "route";

      default:
         SERRX(rotation);
   }

   /* NOTREACHED */
}

const char *
privop2string(op)
   const priv_op_t op;
{
   switch (op) {
      case PRIV_ON:
         return "on";

      case PRIV_OFF:
         return "off";
   }


   /* NOTREACHED */
   SERRX(op);
}

#if !HAVE_PRIVILEGES
char *
userids2string(userids, prefix, str, strsize)
   const struct userid_t *userids;
   const char *prefix;
   char *str;
   size_t strsize;
{
   size_t strused;

   if (strsize == 0) {
      static char buf[128];

      str = buf;
      strsize = sizeof(buf);
   }

   *str    = NUL;
   strused = 0;

   strused += snprintfn(&str[strused], strsize - strused,
   "\"%sprivileged\": \"%s\",\n", prefix, uid2name(userids->privileged));

   strused += snprintfn(&str[strused], strsize - strused,
   "\"%sunprivileged\": \"%s\",\n", prefix, uid2name(userids->unprivileged));

   strused += snprintfn(&str[strused], strsize - strused,
   "\"%slibwrap\": \"%s\",\n", prefix, uid2name(userids->libwrap));

   STRIPTRAILING(str, strused);
   return str;
}
#endif /* !HAVE_PRIVILEGES */

#endif /* !SOCKS_CLIENT */
