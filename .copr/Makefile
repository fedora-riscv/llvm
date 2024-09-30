# See https://docs.pagure.org/copr.copr/user_documentation.html#make-srpm
# See for the --setopt option in the enabling of copr repo see:
# https://pagure.io/copr/copr/issue/184

COPR_USERNAME=$(shell rpm --eval %copr_username)
COPR_PROJECT=$(shell rpm --eval %copr_projectname)
YYYYMMDD=$(shell date +%Y%m%d)

.PHONY: srpm
srpm:
	dnf install -y git tar xz curl --setopt=install_weak_deps=False
	YYYYMMDD=$(YYYYMMDD) ./.copr/snapshot-info.sh > version.spec.inc
	rpmbuild \
		--with=snapshot_build \
		--define "_srcrpmdir $(outdir)" \
		--define "_sourcedir $(shell pwd)" \
		--define "_disable_source_fetch 0" \
		-bs $(spec)
