from unittest import TestCase

from src.install.InstallServiceDiscovery import InstallServiceDiscovery
from src.utils.os.OSProfile import OSProfile


class TestInstallServiceDiscovery(TestCase):
    def test_pkg_catalog_awareness(self):
        for profile in OSProfile:
            self.__check_pkg_catalog_awareness_per_os_profile(profile)

    def __check_pkg_catalog_awareness_per_os_profile(self, profile: OSProfile):
        install_service_discovery = InstallServiceDiscovery(profile)
        self.__check_pkg_catalog_awareness_between_each_service(install_service_discovery)

    def __check_pkg_catalog_awareness_between_each_service(self, install_service_discovery: InstallServiceDiscovery):
        pkg_install_check_service = install_service_discovery.pkg_install_check_service()
        pkg_dependency_dag_provider = install_service_discovery.pkg_dependency_dag_provider()
        installer_resolver = install_service_discovery.installer_resolver()
        self.assertEqual(pkg_install_check_service.aware_pkg_catalogs(),
                         pkg_dependency_dag_provider.aware_pkg_catalogs())
        self.assertEqual(pkg_dependency_dag_provider.aware_pkg_catalogs(),
                         installer_resolver.aware_pkg_catalogs())
