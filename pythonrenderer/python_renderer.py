#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug  3 15:36:22 2021

@author: robert
"""

import numpy as np



import matplotlib.pyplot as plt
import matplotlib.animation as animation



import pythonrenderer.csv_reader as csv_reader


class Renderer(object):
    def __init__(self, trajectory_data):
        self.trajectory_data = trajectory_data
        self.fig = plt.figure(figsize=(10, 10))
        self.ax = self.fig.add_subplot(
            111, autoscale_on=False, xlim=(-40, 40), ylim=(0, 20))
        self.ax.set_aspect('equal')
        #self.ax.grid()
        #self.time_template = 'time = %.1fs'
        #self.time_text = self.ax.text(0.05, 0.9, '', transform=self.ax.transAxes)

        self.ani = animation.FuncAnimation(
            self.fig, self.update, frames=trajectory_data.shape[2], init_func=self.setup_plot, blit=False)

    def setup_plot(self):
        xs = np.array(self.trajectory_data[0, :, 0])
        ys = np.array(self.trajectory_data[1, :, 0])
        
        self.scat = self.ax.scatter(xs, ys)
        return self.scat,

    def update(self, i):
        frame_i = np.array(self.trajectory_data[:, :, i])
        frame_i = frame_i.transpose()
        
        
        self.scat.set_offsets(frame_i)
        return self.scat,


if __name__ == "__main__":
    td = csv_reader.read_trajectory_data_csv("test_wave_01.csv")
    print(td[0, 0, 0] == 1.5)
    plotter = Renderer(td)
