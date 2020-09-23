import os


class SudoRunner:
    # FIXME: the return value of os.system is dependent on system & shell
    @staticmethod
    def run(cmd: str, password: str) -> int:
        with_pw_cmd = cmd.replace('sudo', f"echo {password} | sudo -k -S")
        return os.system(with_pw_cmd)
