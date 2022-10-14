FROM httpd:2.4

RUN rm /usr/local/apache2/htdocs/index.html

RUN sed -i \
        -e 's/^#\(Include .*httpd-ssl.conf\)/\1/' \
        -e 's/^#\(LoadModule .*mod_ssl.so\)/\1/' \
        -e 's/^#\(LoadModule .*mod_socache_shmcb.so\)/\1/' \
        conf/httpd.conf

COPY server.crt /usr/local/apache2/conf
COPY server.key /usr/local/apache2/conf