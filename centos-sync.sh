#!/bin/bash

set -ex

centos_branch=c10s
centos_dir=llvm-centos
fedora_dir=llvm-fedora
fedora_ref=rawhide

bundle=1

script_dir=$(dirname $0)

while [ $# -gt 0 ]; do
  case $1 in
    --no-bundle )
      bundle=0
      ;;
    --centos-branch )
      shift
      centos_branch=$1
      ;;
    --fedora-ref )
      shift
      fedora_ref=$1
      ;;
    * )
      echo "unknown option $1"
      exit 1
      ;;
  esac
  shift
done

git clone --depth 10 -b $centos_branch https://gitlab.com/redhat/centos-stream/rpms/llvm.git $centos_dir
git clone --depth 10 -b $fedora_ref https://src.fedoraproject.org/rpms/llvm.git $fedora_dir
if [ $bundle -eq 1 ]; then
  sed -i 's/^%bcond_with bundle_compat_lib$/%bcond_without bundle_compat_lib/g' $fedora_dir/llvm.spec
fi

rsync --exclude-from=$script_dir/.centos-ignore --delete --cvs-exclude -av $fedora_dir/ $centos_dir/

for f in $centos_dir/tests/*; do
  sed -i 's~https://src.fedoraproject.org/tests/llvm.git~https://gitlab.com/redhat/centos-stream/tests/llvm.git~g' $f
done
