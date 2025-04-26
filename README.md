# 🧠 Philosophers (philo / philo_bonus)

<p align="center">
  <a href="">
    <img src="image_philo.jpeg" alt="libft">
  </a>
</p>

> Project from 42 Cursus – Multithreading / Multiprocessing, Mutexes / Semaphores, and Deadlock Avoidance.

> 42 School project implementing the classic synchronization problem.

---

## 📚 Description

This project is a simulation of the classic **Dining Philosophers Problem**, a concurrency exercise to explore how threads/processes and synchronization mechanisms work in a system.

The bonus version uses **processes** and **semaphores** to manage access to shared resources like forks and logging.

---

## 🛠️ Features

- 🧵 `philo`: threads + mutexes  
- 🔀 `philo_bonus`: processes + semaphores  
- 💀 Reaper thread to detect starvation  
- 🍝 Philosophers eat, sleep, think in cycles  
- 💥 Deadlock avoidance  
- ✅ Optional meal count support

---

## 🧪 Arguments of this project

## 🧠 Arguments

| 🧾 **Argument**                                    | 📖 **Description**                                                  |
|---------------------------------------------------|----------------------------------------------------------------------|
| `number_of_philosophers`                         | 👤 Total number of philosophers (and forks)                          |
| `time_to_die` *(in ms)*                          | 💀 Time a philosopher can stay alive without eating                  |
| `time_to_eat` *(in ms)*                          | 🍝 Duration of eating                                                |
| `time_to_sleep` *(in ms)*                        | 💤 Duration of sleeping                                              |
| `number_of_times_each_philosopher_must_eat` *(optional)* | ✅ Stop simulation when all philosophers have eaten this many times |

## ▶️ How to Use

Once compiled, run the program using the following syntax:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
