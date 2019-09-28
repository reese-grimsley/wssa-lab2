## WSSA Lab 2 - FreeRTOS Introduction
### Reese Grimsley

This repo contains all files for lab 2. Parts 2_2a and 2_2b are different methods of transitioning between the three LEDs and their color combinations. Variant 'a' uses delays and flags to control the flow between tasks; this technique seems like it might be error prone, so variant 'b' was created as well. This sketch uses task handles to suspend and resume tasks such that there is a strict control flow between tasks. 