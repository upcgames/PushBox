import os
import shutil
import glob

script_dir = os.path.dirname(os.path.abspath(__file__))
web_dir = os.path.dirname(script_dir)
repo_root = os.path.dirname(web_dir)

source_audio_dir = os.path.join(repo_root, "Retro Push Box")
target_audio_dir = os.path.join(web_dir, "public", "audio")

os.makedirs(target_audio_dir, exist_ok=True)

wav_files = glob.glob(os.path.join(source_audio_dir, "*.wav"))

copied_count = 0
for wav in wav_files:
    filename = os.path.basename(wav)
    dest = os.path.join(target_audio_dir, filename)
    shutil.copy2(wav, dest)
    copied_count += 1

print(f"✅ Copied {copied_count} .wav audio assets from Retro Push Box/ ➔ web/public/audio/")
