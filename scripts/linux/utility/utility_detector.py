import subprocess


class Detector:

    def __init__(self, utility) -> None:
        self.utility = utility

    def detect(self) -> bool:
        result: bool = subprocess.check_output(f"{self.utility} --version", shell=True)
        if result:
            return True
        else:
            print(f"[{self.utility}] not found.")
            return False

