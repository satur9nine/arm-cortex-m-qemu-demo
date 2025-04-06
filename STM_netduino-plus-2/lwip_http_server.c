#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "lwip/api.h"
#include "lwip/apps/httpd.h"
#include "lwip_http_server.h"


u32_t nPageHits = 0;

size_t terminate_on_crlf(char *str, size_t len) {
    if (str == NULL || len < 2) return len;

    for (size_t i = 0; i < len - 1; i++) {
        if (str[i] == '\r' && str[i + 1] == '\n') {
            str[i] = '\0';
            return i;
        }
    }

    return len; // No \r\n found; length remains unchanged
}

#define MAX_BODY_SIZE 1024
char body[MAX_BODY_SIZE];

static void http_server_serve(struct netconn *conn)
{
  struct netbuf *inbuf;
  err_t recv_err;
  char* buf;
  u16_t buflen;

  /* Read the data from the port, blocking if nothing yet there.
   We assume the request (the part we care about) is in one netbuf */
  recv_err = netconn_recv(conn, &inbuf);

  if (recv_err == ERR_OK)
  {
    if (netconn_err(conn) == ERR_OK)
    {
      netbuf_data(inbuf, (void**)&buf, &buflen);

      /* Is this an HTTP GET command? (only check the first 5 chars, since
      there are other formats for GET, and we're keeping it very simple )*/
      if ((buflen >=5) && (strncmp(buf, "GET /", 5) == 0))
      {
      } // GET

      /* Is this an HTTP POST command? (only check the first 5 chars, since
      there are other formats for GET, and we're keeping it very simple )*/
      if ((buflen >= 5) && (strncmp(buf, "POST /", 5) == 0))
      {
        void *data;
        u16_t len;
        int total_body_received = 0;

        buf[buflen] = '\0';
        printf("Received request:\r\n%s\r\n", buf);

        // Find Content-Length
        char *cl_ptr = strstr(buf, "Content-Length:");
        int content_length = 0;
        if (cl_ptr) {
            sscanf(cl_ptr, "Content-Length: %d", &content_length);
            printf("Content-Length: %d\r\n", content_length);
        }

        // Find start of body (after \r\n\r\n)
        char *body_start = strstr(buf, "\r\n\r\n");
        if (body_start) {
            body_start += 4; // skip \r\n\r\n
            int header_size = body_start - buf;
            int body_bytes_in_first_read = buflen - header_size;

            // Copy what we already have
            memcpy(body, body_start, body_bytes_in_first_read);

              // If we haven't received all the body yet, read more
              while (total_body_received < content_length &&
                netconn_recv(conn, &inbuf) == ERR_OK) {
              do {
                  netbuf_data(inbuf, &data, &len);
                  if (total_body_received + len <= MAX_BODY_SIZE) {
                      memcpy(body + total_body_received, data, len);
                      total_body_received += len;
                  }
              } while (netbuf_next(inbuf) >= 0);
              netbuf_delete(inbuf);
          }

            printf("Received binary body (%d bytes):\r\n", total_body_received);
            for (int i = 0; i < total_body_received; i++) {
                printf("%02X ", (unsigned char)body[i]);
            }
            printf("\r\n");

            // TODO: Process request

        }

        // TODO: Use the last response string for the message
		int resp_len = 0;
		const char *resp_body = "";

        char header[128];
        snprintf(header, sizeof(header),
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: application/octet-stream\r\n"
                 "Content-Length: %u\r\n\r\n",
                 resp_len);

        // Send HTTP header
        netconn_write(conn, (const unsigned char*)header, strlen(header), NETCONN_NOCOPY);

        // Send binary body
        netconn_write(conn, resp_body, resp_len, NETCONN_NOCOPY);
      } // POST
    }
  }
  /* Close the connection (server closes in HTTP) */
  netconn_close(conn);

  /* Delete the buffer (netconn_recv gives us ownership,
   so we have to make sure to deallocate the buffer) */
  netbuf_delete(inbuf);
}


static void http_server_netconn_thread(void *arg)
{
  struct netconn *conn, *newconn;
  err_t err, accept_err;

  /* Create a new TCP connection handle */
  conn = netconn_new(NETCONN_TCP);

  if (conn!= NULL)
  {
    /* Bind to port 80 (HTTP) with default IP address */
    err = netconn_bind(conn, NULL, 80);

    if (err == ERR_OK)
    {
      /* Put the connection into LISTEN state */
      netconn_listen(conn);

      while(1)
      {
        /* accept any incoming connection */
        accept_err = netconn_accept(conn, &newconn);
        if(accept_err == ERR_OK)
        {
          /* serve connection */
          http_server_serve(newconn);

          /* delete connection */
          netconn_delete(newconn);
        }
      }
    }
  }
}


void http_server_netconn_init(void)
{
  sys_thread_new("HTTP", http_server_netconn_thread, NULL, DEFAULT_THREAD_STACKSIZE, osPriorityAboveNormal);
}
