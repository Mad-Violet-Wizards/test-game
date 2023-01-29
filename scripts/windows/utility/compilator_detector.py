import subprocess
import os
import json

class CompilatorDetector:

  def __init__(self):
    self.cwd = os.getcwd()
    pass

  def detect(self):
    print("[CompilatorDetector] Going to detect compilator.")

    if (os.path.exists(f'{self.cwd}\windows\config.json') == False):
      print("[CompilatorDetector] Config file not found. Please run auto-config script first.")

    with open(f'{self.cwd}\windows\config.json', 'rb') as config_file:

      data = config_file.read()

      result = json.loads(data)

      return result