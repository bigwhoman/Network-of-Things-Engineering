# Assignment 4
```c
void setup()
{
    pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
}

// the loop function runs over and over again forever
void loop()
{
    int i;
    int count;
    count = 2;
    for (size_t i = 0; i < count; i++)
    {
        digitalWrite(BUILTIN_LED, LOW); // Turn the LED on (Note that LOW is the voltage level
        delay(500);                      // Wait
        digitalWrite(BUILTIN_LED, HIGH); // Turn the LED off by making the voltage HIGH
        delay(500);
    }

    delay(2000); // Wait for two seconds (to demonstrate the active low LED)
}
```

# Assignment 5

## (a)

This would not be the correct approach because the setup function would only be initialized for the first time and if at some point WiFi access point becomes unavailable we can not access it

## (b)

```c
void loop()
{
  if (WiFi.status() != WL_CONNECTED){
    wifi_client.connect();
    while (WiFi.status() != WL_CONNECTED) {
       delay(500);
       Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address is: ");
    Serial.println(WiFi.localIP());
  }
}
```
# Assignment 6
```python
import min_module as em

if __name__ == "__main__":
    my_list = [1,5,-2,7,9]
    print("The minimum of list is : ", em.get_min(my_list))
```
```python
def get_min(li):
    return min(li)
```

# Assignment 7

## (a)
The difference between a virtual machine and a container is that 
the container does not exactly have an operating system on it as opposed to 
the virtual machine which basically has a full operating system running the apps.

## (b)

Advantages : 
<li> Lightweight and fast compared to VMs 
<li> Easy scaling and deployment with orchestration tools<br>

Disadvantages : 
<li> Less isolation than VMs
<li> Potential security risks if container runtime or images are misconfigured

## (c)

A container is a running instance of a container image - it is the actual execution environment with its own filesystem, network, and isolated process space.<br>
A container image is a read-only template containing the application code, runtime, libraries, dependencies, and configuration needed to create a container.

## (d)

Docker pulls images from Docker Hub (hub.docker.com) by default

## (e)

A container registry is basically a storage and distribution system for container images. Like <b>Docker Hub</b> is actually a container registry. Google and Azure also have their container registries.