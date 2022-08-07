import subprocess

class CmakeDetector:

  def __init__(self):
    pass

  def detect(self):
    result = subprocess.check_output("cmake --version").decode('cp1252')
    
    if result:
      return True
    else:
      print("[CmakeDetector] Cmake not found.")
      return False

