#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Aug  2 22:19:22 2021

@author: robert
"""

import csv
import numpy as np


file_name = "first_test.csv"
export_data_absolute_filename = "../exportdata/" + file_name
DIMENSION = int(2)

#dim coord frame

with open(export_data_absolute_filename) as export_csv:
    reader = csv.reader(export_csv)
    headers = next(reader)
    N_dims = int(len(headers) / DIMENSION)
    frames = []
    for state in reader:
        frames.append(state)
       
        
        
    

trajectory_data = np.ndarray((DIMENSION, N_dims, len(frames)))
for (state, frame_num) in zip(frames, range(len(frames))):
    trajectory_data[0,:,frame_num] = state[0::DIMENSION]
    trajectory_data[1,:,frame_num] = state[1::DIMENSION]
