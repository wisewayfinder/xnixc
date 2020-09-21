from src.utils.os.OSProfile import OSProfile


class OSResolver:
    @staticmethod
    def resolve() -> OSProfile:
        # TODO: add inspection logic
        return OSProfile.UBUNTU_2004
