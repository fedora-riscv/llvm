# See https://docs.pagure.org/copr.copr/user_documentation.html#make-srpm
# See for the --setopt option in the enabling of copr repo see:
# https://pagure.io/copr/copr/issue/184
.PHONY: srpm
srpm:
	dnf install -y dnf-plugins-core fedora-packager python3-dnf-plugin-versionlock
	dnf copr enable -y --setopt=reposdir=/tmp/yum.repos.d @fedora-llvm-team/llvm-snapshot-builder
	dnf install -y --setopt=reposdir=/tmp/yum.repos.d llvm-snapshot-builder
	for p in $(dnf --setopt=reposdir=/tmp/yum.repos.d repoquery llvm* clang* 2>/dev/null); do \
		echo "Locking package: $p"; \
		dnf --setopt=reposdir=/tmp/yum.repos.d versionlock $p; \
	done
	cat /etc/dnf/plugins/versionlock.list
	rpmbuild \
		--define "_srcrpmdir $(outdir)" \
		--define "_sourcedir $(shell pwd)" \
		--define "_disable_source_fetch 0" \
		-bs $(spec)
