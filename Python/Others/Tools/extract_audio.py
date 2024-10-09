# 提取视频中的音频流的小工具
#
# 使用方式：python extract_audio.py "test.mp4" "output_audio.%a"
# 说明：%a 为占位符，表示输入视频中的音频格式。
# 注意事项：
#   1. 需要提前安装 ffmpeg
#   2. 对于有复杂音视频流可能需要修改代码。本代码只获取第1条音频流。

import subprocess

def get_audio_format(video_path):
    result = subprocess.run(["ffmpeg", "-i", video_path], capture_output=True, text=True)
    lines = result.stderr.splitlines()
    for line in lines:
        if "Audio:" in line:
            # print(f"debug audio in line: {line}")
            return line.split("Audio:")[1].split()[0]

def extract_audio(video_path, output_path_template):
    audio_format = get_audio_format(video_path)
    # print(f'audio format: {audio_format}')
    output_path = output_path_template.replace("%a", audio_format)
    command = [
        "ffmpeg",
        "-i", video_path,
        "-vn",
        "-map", "0:a",
        "-c", "copy",
        output_path
    ]
    subprocess.run(command)

if __name__ == "__main__":
    import sys
    
    if len(sys.argv) != 3:
        print("Usage: python extract_audio.py <video_file> <output_template>")
        sys.exit(1)
    
    video_file = sys.argv[1]
    output_template = sys.argv[2]
    
    extract_audio(video_file, output_template)