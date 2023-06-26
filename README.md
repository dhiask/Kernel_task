# Kernel_task
Es soll ein dynamisch ladbares Linux Kernel Modul entwickelt werden, welches gegen die externe Kernel-Buildschnittstelle gebaut wird und die folgenden Interfaces für den Userspace bereitstellt.

Dabei wurden die folgenden Kernel APIs genutzt werden Workqueue/Timer, Liste, Mutex/Semaphor.


1. Beim Laden/Entladen des Moduls soll eine entsprechende Log Nachricht im Kernel Log auftauchen
    => Log Nachricht wird als Kern_Info ussing The Printk Function gesendet  :   printk(KERN_INFO "my_module loaded\n"); 

3. Datenaustausch mit dem Userspace: Es soll ein Interface angelegt werden welches:
2.1. Text-Daten vom Userspace annimmt und in einem dynamischen internen Speicher ablegt
2.2. Text-Daten aus dem internen Speicher an den Userspace zurückgibt
    => Für die Verwaltung des des Dynamischen Speicher  die Funktionen malloc, realloc und free verwendt.

  
3. Benutzung der Kernel API:
3.1. Die Text-Daten aus den internen Speicher sollen regelmässig, 1 Wort pro Sekunde, in das Kernel Log geschrieben werden
Für die Geschwindigkeit der Benuzung des Kernel Log Funktion wir setzen : LOG_INTERVAL_MS auf 1000

Dase ist mein erstes Kernel Modul ist . :) :) :)
