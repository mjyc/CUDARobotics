FROM mcr.microsoft.com/devcontainers/cpp:1.0.0-debian-11

ARG BAZELISK_VERSION="none"
COPY ./install-bazel.sh /tmp/
RUN if [ "${BAZELISK_VERSION}" != "none" ]; then \
        chmod +x /tmp/install-bazel.sh && /tmp/install-bazel.sh ${BAZELISK_VERSION}; \
    fi \
    && rm -f /tmp/install-bazel.sh

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get -y install --no-install-recommends gnuplot

ARG BUILDIFIER_VERSION="none"
COPY ./install-buildifier.sh /tmp/
RUN if [ "${BUILDIFIER_VERSION}" != "none" ]; then \
        chmod +x /tmp/install-buildifier.sh && /tmp/install-buildifier.sh ${BUILDIFIER_VERSION}; \
    fi \
    && rm -f /tmp/install-buildifier.sh

ARG BAZEL_COMPDB_VERSION="none"
COPY ./install-bazel-compdb.sh /tmp/
RUN if [ "${BAZEL_COMPDB_VERSION}" != "none" ]; then \
        chmod +x /tmp/install-bazel-compdb.sh && /tmp/install-bazel-compdb.sh ${BAZEL_COMPDB_VERSION}; \
    fi \
    && rm -f /tmp/install-bazel-compdb.sh