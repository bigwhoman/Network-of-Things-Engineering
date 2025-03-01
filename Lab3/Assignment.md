# Assignment 1

## (a)
First of all, since K3s is an orchestrator, it could 
handle and configure resource limits and requests and also it has built-in 
load balancing. K3s provides RabbitMQ with stateful sets. Also it integrates great with K3s monitoring stack.

## (b)
No, we could install RabbitMQ dirrectly on our OS or we could 
install it via getting its docker image or we could even get it as a service like from AWS or Azure.<br>


## (c)
we have Apache ActiveMQ.<br>
Pros : 
<li> Mature codebase with large community
<li> Built-in message persistence with KahaDB

Cons : 
<li> More complex configuration
<li> Less intuitive management UI

We also have HornetQ.<br>
Pros : 
<li> Built-in persistence
<li> Good documentation

Cons : 
<li> Limited protocol support compared to RabbitMQ
<li> Less flexibility in routing options

# Assignment 2

## (a)
Exchanges receive messages from publishers and distribute them to queues based on routing rules. Queues store messages and deliver them to consumers. Also, exchanges handle message routing logic while queues handle message storage and delivery.


## (b)
Routing keys are message attributes used by exchanges to determine which queues should receive the message. They're typically dot-separated strings like "logs.error".
<br>
Bindings are rules that connect exchanges to queues which specify which routing keys match or any filters to be applied to them.

## (c)
<li> Direct: One-to-one routing using exact routing key matches
<li> Topic: Routes based on routing key patterns using wildcards (* and #)
<li> Fanout: Broadcasts messages to all bound queues, ignoring routing keys
<li> Headers: Routes based on message header attributes instead of routing keys
<li> Default (nameless): Special pre-declared direct exchange


# Assignment 3

## publisher : 

```python
import pika
import logging
import time

prev_msg = ""

def connect_to_broker(ip, port, user, passw):
    credentials = pika.PlainCredentials(user, passw)
    parameters = pika.ConnectionParameters(ip, port, "/",credentials)
    connection = pika.BlockingConnection(parameters)
    channel = connection.channel()
    logging.info("AMQP - Connected to broker: " + str(ip) + ":" + str(port))
    return channel



def create_queue(channel, exchange, routing_key, queue,durable=False):
    channel.queue_declare(queue=queue, durable=durable)
    channel.queue_bind(exchange=exchange, queue=queue,routing_key=routing_key)
    logging.debug("AMQP - Queue declare and bind: " + queue)


if __name__ == "__main__":
    logging.basicConfig(
            format="%(asctime)s | %(name)s | %(levelname)s | %(message)s",level=logging.DEBUG,
    )
    ip = "172.20.10.13"
    port = 30674
    user = "user"
    passw = "password"
    queue = "queue_test"
    exchange = "amq.topic"
    routing_key = "routing_key_test"
    message = "message_test"
    channel = connect_to_broker(ip, port, user, passw)
    create_queue(channel, exchange, routing_key, queue)
    i = 0
    j = 0
    while True:
        if j%5 == 0:
           i += 1 
           message += str(i)
        

        time.sleep(1)
        channel.basic_publish(exchange=exchange, routing_key=routing_key, body=message)
        j += 1

```

## Subscriber

```python
import pika
import logging

prev_msg = ""

def connect_to_broker(ip, port, user, passw):
    credentials = pika.PlainCredentials(user, passw)
    parameters = pika.ConnectionParameters(ip, port, "/",credentials)
    connection = pika.BlockingConnection(parameters)
    channel = connection.channel()
    logging.info("AMQP - Connected to broker: " + str(ip) + ":" + str(port))
    return channel



def create_queue(channel, exchange, routing_key, queue,durable=False):
    channel.queue_declare(queue=queue, durable=durable)
    channel.queue_bind(exchange=exchange, queue=queue,routing_key=routing_key)
    logging.debug("AMQP - Queue declare and bind: " + queue)

def on_message(channel, method, properties, msg):
    if msg.decode("utf-8") != prev_msg :
        logging.debug("AMQP - New Message received: " + msg.decode("utf-8"))

def subscribe(channel, queue, on_message_callback):
    channel.basic_consume(queue, on_message_callback=on_message_callback)
    logging.info("AMQP - Subscribed to: " + queue)

if __name__ == "__main__":
    logging.basicConfig(
            format="%(asctime)s | %(name)s | %(levelname)s | %(message)s",level=logging.DEBUG,
    )
    ip = "172.20.10.13"
    port = 30673
    user = "user"
    passw = "password"
    queue = "queue_test"
    exchange = "amq.topic"
    routing_key = "routing_key_test"
    message = "message_test"
    channel = connect_to_broker(ip, port, user, passw)
    subscribe(channel, queue, on_message)
    channel.start_consuming()
```

