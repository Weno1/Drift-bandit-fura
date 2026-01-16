import sys
import os
import numpy as np
import librosa

def convert_audio_to_bin(input_file, output_file, target_sr=16000, max_val=250):
    print(f"Processing: {input_file}")
    print(f"Target Sample Rate: {target_sr} Hz")

    try:
        # 1. Load and Resample
        y, sr = librosa.load(input_file, sr=target_sr, mono=True)
        
        # 2. Normalize and Scale Data to 8-bit (0-250)
        y_shifted = (y + 1.0) / 2.0
        y_scaled = y_shifted * max_val
        y_clipped = np.clip(y_scaled, 0, max_val)
        y_int = y_clipped.astype(np.uint8)

        # 3. Prepare Header and Write to Binary
        array_len = len(y_int)
        
        # Create an 4-byte header representing the length (uint32)
        # 'little' endian is standard for x86/ARM processors
        header = array_len.to_bytes(4, byteorder='little')

        with open(output_file, 'wb') as f:
            # Write the 4-byte length header first
            f.write(header)
            
            # Write the audio data immediately after
            f.write(y_int.tobytes())

        print(f"Success! Saved to {output_file}")
        print(f"  - Header: 4 bytes (uint32_t length)")
        print(f"  - Data:   {array_len} bytes")
        print(f"  - Total:  {8 + array_len} bytes")

    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python audio_to_bin.py <input_file> [output_file] [sample_rate]")
    else:
        input_path = sys.argv[1]
        
        if len(sys.argv) >= 3:
            output_path = sys.argv[2]
        else:
            filename = os.path.splitext(os.path.basename(input_path))[0]
            output_path = f"{filename}.bin"

        if len(sys.argv) >= 4:
            sample_rate = int(sys.argv[3])
        else:
            sample_rate = 44000

        convert_audio_to_bin(input_path, output_path, target_sr=sample_rate)