# See https://docs.pagure.org/copr.copr/user_documentation.html#make-srpm
# See for the --setopt option in the enabling of copr repo see:
# https://pagure.io/copr/copr/issue/184
.PHONY: srpm
srpm:
	dnf install -y dnf-plugins-core fedora-packager
	dnf copr enable -y --setopt=reposdir=/tmp/yum.repos.d @fedora-llvm-team/llvm-snapshot-builder
	dnf install -y --setopt=reposdir=/tmp/yum.repos.d llvm-snapshot-builder
	rpmdev-spectool --get-files --all --sourcedir llvm.spec
	rpmbuild -bs llvm.spec
	find $(shell rpm --eval "%{_srcrpmdir}") -name "*.src.rpm" -exec cp {} $(outdir) \;
