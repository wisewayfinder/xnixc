import os
import subprocess

from src.install.installer.PkgInstaller import PkgInstaller


class Ubuntu2004CMakeInstaller(PkgInstaller):
    def __init__(self) -> None:
        self.__encoding = 'UTF-8'
        self.__cmake_version = '3.18.2'
        super().__init__()

    def one_line_description(self) -> str:
        return 'CMake'

    def install(self) -> None:
        # TODO: change hard coded clang version to flexible search
        clang_c_location = subprocess.check_output(['which', 'clang-11']).decode(self.__encoding).strip()
        os.system(f"export CC={clang_c_location}")
        clang_cpp_location = subprocess.check_output(['which', 'clang++-11']).decode(self.__encoding).strip()
        os.system(f"export CXX={clang_cpp_location}")
        os.system('sudo apt-get install make')
        os.system('mkdir .tmp')
        os.system(f"wget -P .tmp https://github.com/Kitware/CMake/releases/download/v{self.__cmake_version}/cmake-{self.__cmake_version}.tar.gz")
        os.system(f"cd ./.tmp && tar -xvzf cmake-{self.__cmake_version}.tar.gz")
        os.system(f"cd ./.tmp/cmake-{self.__cmake_version} && ./configure")
        os.system(f"cd ./.tmp/cmake-{self.__cmake_version} && make")
        os.system('sudo apt-get install checkinstall')
        os.system(f"cd ./.tmp/cmake-{self.__cmake_version} && checkinstall")
        raise NotImplementedError
