
YYYYMMDD=$(shell date +%Y%m%d)
OUTDIR=$(shell pwd)/out
SPEC=llvm.spec
BUILDDIR=$(shell pwd)/BUILD
BUILDROOTDIR=$(shell pwd)/BUILD
SOURCEDIR=$(shell pwd)
FEDORA_RELEASE=f39

.PHONY: setup
setup:
	mkdir -pv $(OUTDIR)
	mkdir -pv $(BUILDDIR)
	mkdir -pv $(BUILDROOTDIR)
	mkdir -pv $(SOURCEDIR)

	YYYYMMDD=$(YYYYMMDD) ./.copr/snapshot-info.sh > $(SOURCEDIR)/version.spec.inc

.PHONY: local-srpm
local-srpm: setup
	rpmbuild \
		--define "yyyymmdd $(YYYYMMDD)" \
		--define "_srcrpmdir $(OUTDIR)" \
		--define "_sourcedir $(SOURCEDIR)" \
		--define "_disable_source_fetch 0" \
		-bs $(SPEC)

.PHONY: local-rpm
local-rpm: setup
	fedpkg --release $(FEDORA_RELEASE) -v \
		local \
		--builddir $(BUILDDIR) \
		--buildrootdir $(BUILDROOTDIR) \
		--define "yyyymmdd $(YYYYMMDD)" \
		--define "_disable_source_fetch 0" \
		-- $(SPEC)

.PHONY: local-clean
local-clean:
	-rm -rf $(BUILDDIR)
	-rm -rf $(BUILDROOTDIR)
	-rm -rf $(OUTDIR)
	-rm -f *.txt
	-rm -f *.tar.xz
	-rm -f *.tar.xz.sig
	-rm -rf x86_64
	-rm -rf noarch
	-rm -rf *.src.rpm

.PHONY: local-list-check
local-list-check: setup
	fedpkg --release $(FEDORA_RELEASE) -v \
		local \
		--builddir $(BUILDDIR) \
		--buildrootdir $(BUILDROOTDIR) \
		--define "yyyymmdd $(YYYYMMDD)" \
		--define "_disable_source_fetch 0" \
		-- $(SPEC) -bl

.PHONY: local-prep 
local-prep: setup
	fedpkg --release $(FEDORA_RELEASE) -v \
		prep \
		--builddir $(BUILDDIR) \
		--buildrootdir $(BUILDROOTDIR) \
		--define "yyyymmdd $(YYYYMMDD)" \
		--define "_disable_source_fetch 0" \
		-- $(SPEC)


.PHONY: local-tmt-vm
local-tmt-vm:
	# This is to ensure the required packages are installed
	rpm -q tmt tmt+provision-virtual
	# This is to check if you've started libvirt
	# If this fails, run: sudo systemctl start libvirtd
	# systemctl status libvirtd --no-pager
	# In case of: Failed to boot testcloud instance (authentication unavailable: no polkit agent available to authenticate action 'org.libvirt.unix.manage')
	# Add yourself to libvirt group: sudo usermod -a -G libvirt $USER
	cat /etc/group | grep libvirt | grep $(USER)
	tmt \
		-c distro=fedora-rawhide \
		-c arch=x86_64 \
		-c snapshot=20240124
	run \
		-avv \
	provision \
		-h virtual.testcloud \
		-c system \
		-i fedora-rawhide \
	prepare \
		-h install \
		-c fedora-llvm-team/llvm-snapshots-big-merge-20240124 \
	test \
	report

