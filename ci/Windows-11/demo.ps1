
mkdir   ./Data/Output   -erroraction 'silentlycontinue'
rm      ./Data/Output/* -erroraction 'silentlycontinue'

# DL Image
Start-Process powershell "./build/Demo/Debug/OTP_TX_Image.exe   ./Data/Input/key-aes-a.bin  ./Data/Input/key-otp-a.bin  ./Data/Input/barbara.pgm        25000                                      127.0.0.1   10  2> ./Data/Output/otp_aa_output_transmitter.txt"
                          ./build/Demo/Debug/OTP_RX_Image.exe   ./Data/Input/key-aes-a.bin  ./Data/Input/key-otp-a.bin  ./Data/Output/barbara-aa.pgm    25000                                                  10  2> ./Data/Output/otp_aa_output_receiver.txt

Start-Process powershell "./build/Demo/Debug/OTP_TX_Image.exe   ./Data/Input/key-aes-a.bin  ./Data/Input/key-otp-a.bin  ./Data/Input/barbara.pgm        25100                                      127.0.0.1   10  2> ./Data/Output/otp_ab_output_transmitter.txt"
                          ./build/Demo/Debug/OTP_RX_Image.exe   ./Data/Input/key-aes-a.bin  ./Data/Input/key-otp-b.bin  ./Data/Output/barbara-ab.pgm    25120                                                  10  2> ./Data/Output/otp_ab_output_receiver.txt

Start-Process powershell "./build/Demo/Debug/OTP_TX_Image.exe   ./Data/Input/key-aes-a.bin  ./Data/Input/key-otp-a.bin  ./Data/Input/barbara.pgm        25200                                      127.0.0.1   10  2> ./Data/Output/otp_ba_output_transmitter.txt"
                          ./build/Demo/Debug/OTP_RX_Image.exe   ./Data/Input/key-aes-b.bin  ./Data/Input/key-otp-a.bin  ./Data/Output/barbara-ba.pgm    25200                                                  10  2> ./Data/Output/otp_ba_output_receiver.txt

Start-Process powershell "./build/Demo/Debug/OTP_TX_Image.exe   ./Data/Input/key-aes-a.bin  ./Data/Input/key-otp-a.bin  ./Data/Input/barbara.pgm        25300                                      127.0.0.1   10  2> ./Data/Output/otp_bb_output_transmitter.txt"
                          ./build/Demo/Debug/OTP_RX_Image.exe   ./Data/Input/key-aes-b.bin  ./Data/Input/key-otp-b.bin  ./Data/Output/barbara-bb.pgm    25300                                                  10  2> ./Data/Output/otp_bb_output_receiver.txt

# DL Video
Start-Process powershell "./build/Demo/Debug/OTP_TX_Video.exe   ./Data/Input/key-aes-a.bin  ./Data/Input/key-otp-a.bin  ./Data/Input/Frames-0320x0240   26000                                      127.0.0.1   10  2> ./Data/Output/otp_vid_output_transmitter.txt"
Start-Process powershell "./build/Demo/Debug/Gateway.exe                                                                                                26000 26010         127.0.0.1                          10  2> ./Data/Output/mp_gateway_OTP_TX.txt"

Start-Process powershell "./build/Demo/Debug/Gateway.exe                                                                                                26010 26020         127.0.0.1                          10  2> ./Data/Output/mp_gateway_OTP_RX.txt"
                          ./build/Demo/Debug/OTP_RX_Video.exe   ./Data/Input/key-aes-a.bin  ./Data/Input/key-otp-a.bin                                  26020                                                  10  2> ./Data/Output/otp_vid_output_receiver.txt

# MP Video
Start-Process powershell "./build/Demo/Debug/MP_TX_Video.exe    ./Data/Input/key-aes-a.bin  ./Data/Input/key-otp-a.bin  ./Data/Input/Frames-0320x0240   27010 27020 27030  127.0.0.1   127.0.0.1   127.0.0.1   10  2> ./Data/Output/mp_vid_output_transmitter.txt"
Start-Process powershell "./build/Demo/Debug/Gateway.exe                                                                                                27010 27011        127.0.0.1                           10  2> ./Data/Output/mp_gateway_MP_T0.txt"
Start-Process powershell "./build/Demo/Debug/Gateway.exe                                                                                                27020 27021                    127.0.0.1               10  2> ./Data/Output/mp_gateway_MP_T1.txt"
Start-Process powershell "./build/Demo/Debug/Gateway.exe                                                                                                27030 27031                                127.0.0.1   10  2> ./Data/Output/mp_gateway_MP_T2.txt"

Start-Process powershell "./build/Demo/Debug/Gateway.exe                                                                                                27011 27012        127.0.0.1                           10  2> ./Data/Output/mp_gateway_MP_R0.txt"
Start-Process powershell "./build/Demo/Debug/Gateway.exe                                                                                                27021 27022                    127.0.0.1               10  2> ./Data/Output/mp_gateway_MP_R1.txt"
Start-Process powershell "./build/Demo/Debug/Gateway.exe                                                                                                27031 27032                                127.0.0.1   10  2> ./Data/Output/mp_gateway_MP_R2.txt"
                          ./build/Demo/Debug/MP_RX_Video.exe                                                                                            27012 27022 27032                                      10  2> ./Data/Output/mp_vid_output_receiver.txt

# Integrity Check Video Attacker-001-Dummy
Start-Process powershell "./build/Demo/Debug/IC_TX_Video.exe                                                            ./Data/Input/Frames-0320x0240   28000              127.0.0.1                           10  2> ./Data/Output/ic_vid_output_transmitter_001.txt"
Start-Process powershell "./build/Demo/Debug/Attacker-001.exe                                                                                           28000 28010        127.0.0.1                           10  2> ./Data/Output/ic_attacker_001.txt"
                          ./build/Demo/Debug/IC_RX_Video.exe                                                                                            28010                                                  10  2> ./Data/Output/ic_vid_output_receiver_001.txt

# Integrity Check Video Attacker-002-Modify
Start-Process powershell "./build/Demo/Debug/IC_TX_Video.exe                                                            ./Data/Input/Frames-0320x0240   28000              127.0.0.1                           10  2> ./Data/Output/ic_vid_output_transmitter_002.txt"
Start-Process powershell "./build/Demo/Debug/Attacker-002.exe                                                                                           28000 28010        127.0.0.1                           10  2> ./Data/Output/ic_attacker_002.txt"
                          ./build/Demo/Debug/IC_RX_Video.exe                                                                                            28010                                                  10  2> ./Data/Output/ic_vid_output_receiver_002.txt

# Integrity Check Video Attacker-003-Drop
Start-Process powershell "./build/Demo/Debug/IC_TX_Video.exe                                                            ./Data/Input/Frames-0320x0240   28000              127.0.0.1                           10  2> ./Data/Output/ic_vid_output_transmitter_003.txt"
Start-Process powershell "./build/Demo/Debug/Attacker-003.exe                                                                                           28000 28010        127.0.0.1                           10  2> ./Data/Output/ic_attacker_003.txt"
                          ./build/Demo/Debug/IC_RX_Video.exe                                                                                            28010                                                  10  2> ./Data/Output/ic_vid_output_receiver_003.txt

# Integrity Check Video Attacker-004-Ramdom
Start-Process powershell "./build/Demo/Debug/IC_TX_Video.exe                                                            ./Data/Input/Frames-0320x0240   28000              127.0.0.1                           10  2> ./Data/Output/ic_vid_output_transmitter_004.txt"
Start-Process powershell "./build/Demo/Debug/Attacker-004.exe                                                                                           28000 28010        127.0.0.1                           10  2> ./Data/Output/ic_attacker_004.txt"
                          ./build/Demo/Debug/IC_RX_Video.exe                                                                                            28010                                                  10  2> ./Data/Output/ic_vid_output_receiver_004.txt
