from getpass import getpass
from src.install.installer.PkgInstaller import PkgInstaller
from src.utils.os.SudoRunner import SudoRunner


class SudoInstaller(PkgInstaller):
    def __init__(self) -> None:
        self.__is_set: bool = False
        self.__password: str = ''
        super().__init__()

    def one_line_description(self) -> str:
        return "Caching 'su' password to made other task automatically"

    def install(self) -> None:
        if not self.__is_set:
            tmp_pw = getpass()
        else:
            print('It looks password already set, do you want change? [y]: ',
                  end='')
            want_change = input().lower()
            if want_change == 'y' or want_change == '':
                tmp_pw = getpass()
            else:
                print('Keep caching password')
                return

        if tmp_pw is not None:
            try:
                SudoInstaller.__check_password_right(tmp_pw)
                self.__is_set = True
                self.__password = tmp_pw
                print('set password successfully done')
            except ValueError as e:
                print(e)

    @staticmethod
    def __check_password_right(tmp_pw: str):
        res = SudoRunner.run('sudo ls >/dev/null 2>&1', tmp_pw)
        if res is not 0:
            raise ValueError('given password looks not valid, please check')
