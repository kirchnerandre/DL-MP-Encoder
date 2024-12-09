#!/bin/bash

mkdir   ./Data/Output   2> /dev/null
rm      ./Data/Output/* 2> /dev/null

# DL Image
./build/Demo/OTP_TX_Image.exe   ./Data/Input/key-aes-a.bin ./Data/Input/key-otp-a.bin ./Data/Input/barbara.pgm          25000               127.0.0.1   10  2> ./Data/Output/otp_aa_output_transmitter.txt  &
./build/Demo/OTP_RX_Image.exe   ./Data/Input/key-aes-a.bin ./Data/Input/key-otp-a.bin ./Data/Output/barbara-aa.pgm      25000                           10  2> ./Data/Output/otp_aa_output_receiver.txt     &
wait

./build/Demo/OTP_TX_Image.exe   ./Data/Input/key-aes-a.bin ./Data/Input/key-otp-a.bin ./Data/Input/barbara.pgm          25100               127.0.0.1   10  2> ./Data/Output/otp_ab_output_transmitter.txt  &
./build/Demo/OTP_RX_Image.exe   ./Data/Input/key-aes-a.bin ./Data/Input/key-otp-b.bin ./Data/Output/barbara-ab.pgm      25100                           10  2> ./Data/Output/otp_ab_output_receiver.txt     &
wait

./build/Demo/OTP_TX_Image.exe   ./Data/Input/key-aes-a.bin ./Data/Input/key-otp-a.bin ./Data/Input/barbara.pgm          25200               127.0.0.1   10  2> ./Data/Output/otp_ba_output_transmitter.txt  &
./build/Demo/OTP_RX_Image.exe   ./Data/Input/key-aes-b.bin ./Data/Input/key-otp-a.bin ./Data/Output/barbara-ba.pgm      25200                           10  2> ./Data/Output/otp_ba_output_receiver.txt     &
wait

./build/Demo/OTP_TX_Image.exe   ./Data/Input/key-aes-a.bin ./Data/Input/key-otp-a.bin ./Data/Input/barbara.pgm          25300               127.0.0.1   10  2> ./Data/Output/otp_bb_output_transmitter.txt  &
./build/Demo/OTP_RX_Image.exe   ./Data/Input/key-aes-b.bin ./Data/Input/key-otp-b.bin ./Data/Output/barbara-bb.pgm      25300                           10  2> ./Data/Output/otp_bb_output_receiver.txt     &
wait

# DL Video
./build/Demo/OTP_TX_Video.exe   ./Data/Input/key-aes-a.bin ./Data/Input/key-otp-a.bin ./Data/Input/Frames-0320x0240     26000               127.0.0.1   10  2> ./Data/Output/otp_vid_output_transmitter.txt &
./build/Demo/Debug/Gateway.exe                                                                                          26000 26010         127.0.0.1   10  2> ./Data/Output/mp_gateway_OTP_TX.txt"         &

./build/Demo/Debug/Gateway.exe                                                                                          26010 26020         127.0.0.1   10  2> ./Data/Output/mp_gateway_OTP_R0.txt"         &
./build/Demo/OTP_RX_Video.exe   ./Data/Input/key-aes-a.bin ./Data/Input/key-otp-a.bin                                         26020                     10  2> ./Data/Output/otp_vid_output_receiver.txt    &
wait

# MP Video
./build/Demo/MP_TX_Video.exe    ./Data/Input/key-aes-a.bin ./Data/Input/key-otp-a.bin ./Data/Input/Frames-0320x0240     27010 27020 27030   127.0.0.1 127.0.0.1 127.0.0.1   10  2> ./Data/Output/mp_vid_output_transmitter.txt  &
./build/Demo/Debug/Gateway.exe                                                                                          27010 27011         127.0.0.1                       10  2> ./Data/Output/mp_gateway_MP_T0.txt"          &
./build/Demo/Debug/Gateway.exe                                                                                          27020 27021                   127.0.0.1             10  2> ./Data/Output/mp_gateway_MP_T1.txt"          &
./build/Demo/Debug/Gateway.exe                                                                                          27030 27031                             127.0.0.1   10  2> ./Data/Output/mp_gateway_MP_T2.txt"          &

./build/Demo/Debug/Gateway.exe                                                                                          27011 27012         127.0.0.1                       10  2> ./Data/Output/mp_gateway_MP_R0.txt"          &
./build/Demo/Debug/Gateway.exe                                                                                          27021 27022                   127.0.0.1             10  2> ./Data/Output/mp_gateway_MP_R1.txt"          &
./build/Demo/Debug/Gateway.exe                                                                                          27031 27032                             127.0.0.1   10  2> ./Data/Output/mp_gateway_MP_R2.txt"          &
./build/Demo/MP_RX_Video.exe                                                                                            27012 27022 27032                                   10  2> ./Data/Output/mp_vid_output_receiver.txt     &
wait

# Integrity Check Video
./build/Demo/IC_TX_Video.exe                                                        ./Data/Input/Frames-0320x0240    28000               127.0.0.1   10  2> ./Data/Output/ic_vid_output_transmitter.txt  &
./build/Demo/IC_RX_Video.exe                                                                                         28000                           10  2> ./Data/Output/ic_vid_output_receiver.txt     &
wait
