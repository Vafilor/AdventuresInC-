FROM ubuntu:16.04

ENV DEBIAN_FRONTEND noninteractive

# Install packages
ADD provision.sh /provision.sh
ADD run.sh /run.sh

RUN chmod +x /*.sh

RUN ./provision.sh

CMD /run.sh