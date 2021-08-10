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
        self.fig = plt.figure(figsize=(7, 7))
        self.ax = self.fig.add_subplot(
            111, autoscale_on=False, xlim=(-11, 11), ylim=(-1, 21))
        self.ax.set_aspect('equal')

        #self.time_template = 'time = %.1fs'
        #self.time_text = self.ax.text(0.05, 0.9, '', transform=self.ax.transAxes)

        self.setup_plot()

        self.ani = animation.FuncAnimation(
                                    self.fig, 
                                    self.update, 
                                    frames=trajectory_data.shape[2], 
                                    interval=1_000/60,
                                    repeat=True, 
                                    blit=True)
        plt.show()

    def setup_plot(self):
        xs = [] #np.array(self.trajectory_data[0, :, 0])
        ys = [] #np.array(self.trajectory_data[1, :, 0])
        
        self.scat = self.ax.scatter(xs, ys)

        
        # Major ticks every 20, minor ticks every 5
        major_x_ticks = np.linspace(-10, 10, 4+1)
        minor_x_ticks = np.linspace(-10, 10, 20+1)

        major_y_ticks = np.linspace(0, 20, 4+1)
        minor_y_ticks = np.linspace(0, 20, 20+1)

        self.ax.set_xticks(major_x_ticks)
        self.ax.set_xticks(minor_x_ticks, minor=True)
        self.ax.set_yticks(major_y_ticks)
        self.ax.set_yticks(minor_y_ticks, minor=True)

        self.ax.grid(which='both')

        self.ax.grid(which='minor', alpha=0.2)
        self.ax.grid(which='major', alpha=0.5)

    def update(self, i):
        frame_i = np.array(self.trajectory_data[:, :, i])
        frame_i = frame_i.transpose()
        
        
        self.scat.set_offsets(frame_i)
        return self.scat,


if __name__ == "__main__":
    td = csv_reader.read_trajectory_data_csv("test_wave_01.csv")
    print(td[0, 0, 0] == 1.5)
    plotter = Renderer(td)
