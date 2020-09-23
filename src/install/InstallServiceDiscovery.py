from typing import Optional

from src.utils.os.OSProfile import OSProfile
from src.install.check.PkgInstallCheckService import PkgInstallCheckService
from src.install.check.Ubuntu2004PkgInstallCheckService import Ubuntu2004PkgInstallCheckService
from src.install.dependency.PkgDependencyDagProvider import PkgDependencyDagProvider
from src.install.dependency.Ubuntu2004PkgDependencyDagProvider import Ubuntu2004PkgDependencyDagProvider
from src.install.installer.PkgInstallerResolver import PkgInstallerResolver
from src.install.installer.ubuntu2004.Ubuntu2004PkgInstallerResolver import Ubuntu2004PkgInstallerResolver


class InstallServiceDiscovery:
    def __init__(self, os_profile: OSProfile) -> None:
        self.__os_profile = os_profile
        super().__init__()

    def pkg_install_check_service(self) -> PkgInstallCheckService:
        if self.__is_ubuntu_2004():
            return Ubuntu2004PkgInstallCheckService()
        self.__raise_unknown_os_error()

    def pkg_dependency_dag_provider(self) -> PkgDependencyDagProvider:
        if self.__is_ubuntu_2004():
            return Ubuntu2004PkgDependencyDagProvider()
        self.__raise_unknown_os_error()

    def installer_resolver(self, sudo_password: Optional[str] = None) -> PkgInstallerResolver:
        if self.__is_ubuntu_2004():
            return Ubuntu2004PkgInstallerResolver() if sudo_password is None else Ubuntu2004PkgInstallerResolver(sudo_password)
        self.__raise_unknown_os_error()

    def __is_ubuntu_2004(self) -> bool:
        return self.__os_profile == OSProfile.UBUNTU_2004

    def __raise_unknown_os_error(self):
        raise ValueError(f"unknown os {self.__os_profile}")
