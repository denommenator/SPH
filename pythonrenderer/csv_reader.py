#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Aug  2 22:19:22 2021

@author: robert
"""

import csv
import numpy as np

def read_trajectory_data_csv(filename):
    export_data_absolute_filename = "../exportdata/" + filename
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

    return trajectory_data

if __name__ == "__main__":
    td = read_trajectory_data_csv("first_test.csv")
    print(td[0,0,0] == 1.5)
    print(td[0,1,0] == .2)
    print(td[0,2,0] == .4)
    
    print(td[1,0,0] == .5)
    print(td[1,1,0] == .2)
    print(td[1,2,0] == .5)