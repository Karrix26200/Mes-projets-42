import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

def launch_animation(data, curve_history, accuracy, cost_history, generation):
    fig  = plt.figure(figsize=(10, 7))

    plt.subplot(2, 1, 1)
    plt.title('Evolution of Car Prices according to their Km Number')
    plt.xlabel('km')
    plt.ylabel('prices')
    plt.scatter(data['km'], data['price'], label='initial data')
    line, = plt.plot([],[], c='r', label='regression') 
    plt.xlim(0, 250000)
    plt.ylim(3000, 9000)
    plt.legend()
    plt.subplot(2, 2, 3)
    plt.title('Accuracy')
    plt.xlabel('iterations')
    plt.ylabel('percents')
    plt.ylim(ymax = 100, ymin = 0)
    plt.text(5, 85, 'final accuracy: ' + str(round(accuracy[-1],2)) + '%')
    plt.plot(range(generation), accuracy)
    plt.subplot(2, 2, 4)
    plt.title('Cost Function')
    plt.xlabel('iterations')
    plt.plot(range(generation), cost_history)
    plt.tight_layout(pad=2.0)

    def animate(i): 
        line.set_data(data['km'], curve_history[i])
        return line,

    ani = animation.FuncAnimation(fig, animate, init_func=line.set_data([],[]), frames=generation, blit=True, interval=1, repeat=False)

    plt.show()