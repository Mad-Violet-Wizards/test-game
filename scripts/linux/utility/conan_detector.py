import subprocess
import os
import json

class ConanDetector:

  def __init__(self):
    pass

  def detect(self):
    result = subprocess.check_output("conan --version").decode('cp1252')
    
    if result:
      return True
    else:
      print("[ConanDetector] Conan not found.")
      return False
