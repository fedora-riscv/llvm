#!/usr/bin/bash

# You need these packages to run this script: git tar xz curl-minimal

set -e
set +x

# This is important for systems that have a different local but want to produce
# a valid changelog date. 
LANG=en_EN

function loginfo() {
    local msg=$1
    >&2 echo "[INFO]" $msg
}

loginfo "Determine date in YYYYMMDD form"
llvm_snapshot_yyyymmdd=$(date +%Y%m%d)
[[ ! -z "${YYYYMMDD}" ]] && llvm_snapshot_yyyymmdd=$YYYYMMDD

loginfo "Get the source tarball"
tarball_url=https://github.com/kwk/llvm-daily-fedora-rpms/releases/download/source-snapshot/llvm-project-${llvm_snapshot_yyyymmdd}.src.tar.xz
tarball=llvm-project-${llvm_snapshot_yyyymmdd}.src.tar.xz
if [ -e $tarball ]; then
    loginfo "Source tarball already exists: $tarball"
else
    loginfo "Downloading source tarball $tarball from $tarball_url"
    curl -sL -o $tarball ${tarball_url}
fi

loginfo "Grab git revision from tarball"
llvm_snapshot_git_revision=$(xzcat $tarball | git get-tar-commit-id)
llvm_snapshot_git_revision_short=$(echo "${llvm_snapshot_git_revision:0:14}")

versionfile=llvm-project*.src/cmake/Modules/LLVMVersion.cmake
loginfo "Extract the ${versionfile} file from the source tarball"
if [ -e $versionfile ]; then
    loginfo "CMakeLists.txt already exists: ${versionfile}"
else
    tar -xf $tarball $versionfile
fi

loginfo "Parse ${versionfile} for the LLVM version"
llvm_snapshot_version=$(grep -ioP 'set\(\s*LLVM_VERSION_(MAJOR|MINOR|PATCH)\s\K[0-9]+' ${versionfile} | paste -sd '.')
llvm_snapshot_version_major=$(echo $llvm_snapshot_version | cut -f1 -d.)
llvm_snapshot_version_minor=$(echo $llvm_snapshot_version | cut -f2 -d.)
llvm_snapshot_version_patch=$(echo $llvm_snapshot_version | cut -f3 -d.)
llvm_snapshot_version_suffix=pre${llvm_snapshot_yyyymmdd}.g${llvm_snapshot_git_revision_short}
llvm_snapshot_version_tag=${llvm_snapshot_version}~${llvm_snapshot_version_suffix}
llvm_snapshot_changelog_entry="* $(date +'%a %b %d %Y') LLVM snapshot - ${llvm_snapshot_version_tag}"

tempfile=$(mktemp)
cat > $tempfile <<EOF
%global maj_ver ${llvm_snapshot_version_major}
%global min_ver ${llvm_snapshot_version_minor}
%global patch_ver ${llvm_snapshot_version_patch}
%undefine rc_ver

%global llvm_snapshot_version            ${llvm_snapshot_version}
%global llvm_snapshot_version_tag        ${llvm_snapshot_version_tag}
%global llvm_snapshot_version_major      ${llvm_snapshot_version_major}
%global llvm_snapshot_version_minor      ${llvm_snapshot_version_minor}
%global llvm_snapshot_version_patch      ${llvm_snapshot_version_patch}
%global llvm_snapshot_yyyymmdd           ${llvm_snapshot_yyyymmdd}
%global llvm_snapshot_git_revision       ${llvm_snapshot_git_revision}
%global llvm_snapshot_git_revision_short ${llvm_snapshot_git_revision_short}
%global llvm_snapshot_version_suffix     ${llvm_snapshot_version_suffix}
%global llvm_snapshot_changelog_entry    ${llvm_snapshot_changelog_entry}
%global llvm_snapshot_source_prefix      https://github.com/kwk/llvm-daily-fedora-rpms/releases/download/source-snapshot/
EOF

# One for logs
cat $tempfile >&2

# One to redirect it away
cat $tempfile
