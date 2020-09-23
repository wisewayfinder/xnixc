import os
import subprocess
from typing import Dict, Callable, Optional

from src.install.installer.WithPwPkgInstaller import WithPwPkgInstaller
from src.install.installer.ubuntu2004.Ubuntu2004ClangInstaller import Ubuntu2004ClangInstaller


class Ubuntu2004CMakeInstaller(WithPwPkgInstaller):
    def __init__(self, sudo_password: Optional[str] = None) -> None:
        self.__encoding = 'UTF-8'
        self.__cmake_version = '3.18.2'
        super().__init__(sudo_password)

    def one_line_description(self) -> str:
        return 'CMake'

    def install(self) -> None:
        clang_version = Ubuntu2004ClangInstaller.clang_version()
        install_map: Dict[int, Callable[[], None]] = {
            11: lambda: self.__install_with_clang_11()
        }
        if clang_version not in install_map.keys():
            raise KeyError(f"to install CMake, unknown clang version {clang_version}")
        install_map[clang_version]()

    def __install_with_clang_11(self) -> None:
        clang_c_location = subprocess.check_output(['which', 'clang-11']).decode(self.__encoding).strip()
        clang_cpp_location = subprocess.check_output(['which', 'clang++-11']).decode(self.__encoding).strip()
        self._do_with_pw('sudo apt-get install -y make')
        os.system(f"mkdir {Ubuntu2004CMakeInstaller.__tmp_path()}")
        os.system(f"wget -P {Ubuntu2004CMakeInstaller.__tmp_path()} https://github.com/Kitware/CMake/releases/download/v{self.__cmake_version}/cmake-{self.__cmake_version}.tar.gz")
        os.system(f"cd {Ubuntu2004CMakeInstaller.__tmp_path()} && tar -xvzf cmake-{self.__cmake_version}.tar.gz")
        self._do_with_pw('sudo apt-get install libssl-dev')  # to prevent https://stackoverflow.com/questions/16248775/cmake-not-able-to-find-openssl-library issue
        os.system(f"export CC={clang_c_location} && export CXX={clang_cpp_location} && cd ./.tmp/cmake-{self.__cmake_version} && ./configure")
        os.system(f"cd {Ubuntu2004CMakeInstaller.__tmp_path()}/cmake-{self.__cmake_version} && make")
        self._do_with_pw('sudo apt-get install -y checkinstall')
        os.system(f"cd {Ubuntu2004CMakeInstaller.__tmp_path()}/cmake-{self.__cmake_version} && checkinstall -y")
        os.system(f"rm -rf {Ubuntu2004CMakeInstaller.__tmp_path()}")

    @staticmethod
    def __tmp_path() -> str:
        return './.tmp'
