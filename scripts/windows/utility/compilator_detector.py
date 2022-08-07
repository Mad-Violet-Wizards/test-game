import subprocess
import os
import json

class CompilatorDetector:

  def __init__(self):
    self.cwd = os.getcwd()
    pass

  def detect(self):
    print("[CompilatorDetector] Going to detect compilator.")
    os.chdir('C:/Program Files (x86)/Microsoft Visual Studio/Installer/')
    result = json.loads(subprocess.check_output(f"{os.getcwd()}/vswhere.exe -latest -format json").decode('cp1252'))

    major_version = result[0]["installationVersion"].split(".")[0]

    release_date = result[0]["catalog"]["productLineVersion"]

    os.chdir(self.cwd)

    return { "compilator": "Visual Studio", "version": major_version, "release_date": release_date }