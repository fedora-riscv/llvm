
YYYYMMDD=$(shell date +%Y%m%d)
SOURCEDIR=$(shell pwd)
SPEC=llvm.spec
FEDORA_RELEASE=f40

# Map deprecated targets to new targets
.PHONY: setup local-rpm local-srpm local-prep local-clean
setup local-rpm local-srpm local-prep local-clean:
	$(eval mapped_target:=$(subst setup,snapshot-setup,$(MAKECMDGOALS)))
	$(eval mapped_target:=$(subst local-clean,snapshot-clean,$(mapped_target)))
	$(eval mapped_target:=$(subst local-,snapshot-,$(mapped_target)))
	$(info WARNING: "$(MAKECMDGOALS)" is deprecated. Instead running "$(mapped_target)")
	$(MAKE) $(mapped_target)

.PHONY: snapshot-vars
snapshot-vars:
	$(eval RESULTDIR:=$(shell pwd)/snapshot-results)

.PHONY: release-vars
release-vars:
	$(eval RESULTDIR:=$(shell pwd)/release-results)

.PHONY: prep
prep:
	mkdir -pv $(RESULTDIR)

.PHONY: snapshot-setup
snapshot-setup: snapshot-vars prep
	YYYYMMDD=$(YYYYMMDD) ./.copr/snapshot-info.sh > $(SOURCEDIR)/version.spec.inc
	spectool -g --define "_sourcedir $(SOURCEDIR)" --define "_with_snapshot_build 1" $(SPEC)

.PHONY: release-setup
release-setup: release-vars prep
	spectool -g --define "_sourcedir $(SOURCEDIR)" $(SPEC)

.PHONY: snapshot-srpm
snapshot-srpm: snapshot-setup
	rpmbuild \
		--with=snapshot_build \
		--define "_rpmdir $(RESULTDIR)" \
		--define "_sourcedir $(SOURCEDIR)" \
		--define "_specdir $(SOURCEDIR)" \
		--define "_srcrpmdir $(RESULTDIR)" \
		--define "_builddir $(RESULTDIR)" \
		-bs $(SPEC)

.PHONY: release-srpm
release-srpm: release-setup
	rpmbuild \
		--define "_rpmdir $(RESULTDIR)" \
		--define "_sourcedir $(SOURCEDIR)" \
		--define "_specdir $(SOURCEDIR)" \
		--define "_srcrpmdir $(RESULTDIR)" \
		--define "_builddir $(RESULTDIR)" \
		-bs $(SPEC)

.PHONY: snapshot-rpm
snapshot-rpm: snapshot-setup
	rpmbuild \
		--with=snapshot_build \
		--define "_rpmdir $(RESULTDIR)" \
		--define "_sourcedir $(SOURCEDIR)" \
		--define "_specdir $(SOURCEDIR)" \
		--define "_srcrpmdir $(RESULTDIR)" \
		--define "_builddir $(RESULTDIR)" \
		--noclean \
		-bb $(SPEC)

.PHONY: release-rpm
release-rpm: release-setup
	rpmbuild \
		--define "_rpmdir $(RESULTDIR)" \
		--define "_sourcedir $(SOURCEDIR)" \
		--define "_specdir $(SOURCEDIR)" \
		--define "_srcrpmdir $(RESULTDIR)" \
		--define "_builddir $(RESULTDIR)" \
		--noclean \
		-bb $(SPEC)

.PHONY: snapshot-clean
snapshot-clean: snapshot-vars _clean

.PHONY: release-clean
release-clean: release-vars _clean

.PHONY: _clean
_clean:
	-rm -rf $(RESULTDIR)
	-rm -f *.txt
	-rm -f *.tar.xz
	-rm -f *.tar.xz.sig
	-rm -rf $(shell uname -m)
	-rm -rf noarch
	-rm -rf *.src.rpm
	-rm -rf /tmp/lto-llvm-*.o

.PHONY: snapshot-prep
snapshot-prep: snapshot-setup
	rpmbuild \
		--with=snapshot_build \
		--define "_rpmdir $(RESULTDIR)" \
		--define "_sourcedir $(SOURCEDIR)" \
		--define "_specdir $(SOURCEDIR)" \
		--define "_srcrpmdir $(RESULTDIR)" \
		--define "_builddir $(RESULTDIR)" \
		--noclean \
		-bp $(SPEC)

.PHONY: release-prep
release-prep: releae-setup
	rpmbuild \
		--define "_rpmdir $(RESULTDIR)" \
		--define "_sourcedir $(SOURCEDIR)" \
		--define "_specdir $(SOURCEDIR)" \
		--define "_srcrpmdir $(RESULTDIR)" \
		--define "_builddir $(RESULTDIR)" \
		--noclean \
		-bp $(SPEC)

# .PHONY: local-list-check
# local-list-check: setup
# 	fedpkg --release $(FEDORA_RELEASE) -v \
# 		local \
# 		--builddir $(BUILDDIR) \
# 		--buildrootdir $(BUILDROOTDIR) \
#
# 		--with=snapshot_build \
# 		-- $(SPEC) -bl

# .PHONY: local-tmt-vm
# local-tmt-vm:
# 	# This is to ensure the required packages are installed
# 	rpm -q tmt tmt+provision-virtual
# 	# This is to check if you've started libvirt
# 	# If this fails, run: sudo systemctl start libvirtd
# 	# systemctl status libvirtd --no-pager
# 	# In case of: Failed to boot testcloud instance (authentication unavailable: no polkit agent available to authenticate action 'org.libvirt.unix.manage')
# 	# Add yourself to libvirt group: sudo usermod -a -G libvirt $USER
# 	cat /etc/group | grep libvirt | grep $(USER)
# 	tmt \
# 		-c distro=fedora-rawhide \
# 		-c arch=x86_64 \
# 		-c snapshot=20240124
# 	run \
# 		-avv \
# 	provision \
# 		-h virtual.testcloud \
# 		-c system \
# 		-i fedora-rawhide \
# 	prepare \
# 		-h install \
# 		-c fedora-llvm-team/llvm-snapshots-big-merge-20240124 \
# 	test \
# 	report
