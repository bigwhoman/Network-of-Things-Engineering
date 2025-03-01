# Assignment 1

## (a)
Being schema-free means that you can index and search documents without specifying their structure in advance.

<br>

Key differences with a traditional SQL database : 
<li> Elastic search is optimized for search/analytic on huge volumes of data while SQL servers are optimized for transactions and structured data operations.

<li> Elastic uses JSON-based queries while SQL servers use SQL 

<li> While SQL preserves ACID, Elastic does not necessarily preserve it.

## (b)
1. Apache Solr 
<br>
Pros :
<li>
Extensive Plugin Ecosystem
<li>
Strong Community

<br>
Cons : 
<li>
Less scalable then elastic
<li>
More complex configuration

2. Typesense 
<br>
Pros :
<li>
Simple setup
<li>
Low memory usage

<br>
Cons :
<li>
Smaller Community
<li>
Less flexible schema
    
## (c)
<li> Get : Retrieve data from the server
<li> Post : Create a new resource on the server
<li> Put : Update existing resource 
<li> Patch : Partially update an existing resource
<li> Delete : Remove a resource

# Assignment 2

## (a)
```bash
curl -H "Content-Type: application/json" -XPOST "http://$SERVER_IP:32200/notelab/temperature_topic/1" -d '{"id":"tester", "temperature":22}'
sleep 1
curl -H "Content-Type: application/json" -XPOST "http://$SERVER_IP:32200/notelab/temperature_topic/2" -d '{"id":"toaser", "temperature":55}'
sleep 1
curl -H "Content-Type: application/json" -XPOST "http://$SERVER_IP:32200/notelab/temperature_topic/3" -d '{"id":"rooster", "temperature":65}'
```

Output : 

```
{"_index":"notelab","_type":"temperature_topic","_id":"1","_version":7,"result":"updated","_sh
ards":{"total":2,"successful":1,"failed":0},"_seq_no":9,"_primary_term":1}{"_index":"notelab",
"_type":"temperature_topic","_id":"2","_version":1,"result":"created","_shards":{"total":2,"su
ccessful":1,"failed":0},"_seq_no":10,"_primary_term":1}{"_index":"notelab","_type":"temperatur
e_topic","_id":"3","_version":1,"result":"created","_shards":{"total":2,"successful":1,"failed
":0},"_seq_no":11,"_primary_term":1}
```


## (b)
```bash
curl -XGET "http://$SERVER_IP:32200/notelab/_search?pretty" -H 'Content-Type: application/json' -d '{"query":{"match":{"id":{"query":"rooster"}}}}'
```

Output : 

```

{
  "took" : 1,
  "timed_out" : false,
  "_shards" : {
    "total" : 1,
    "successful" : 1,
    "skipped" : 0,
    "failed" : 0
  },
  "hits" : {
    "total" : {
      "value" : 1,
      "relation" : "eq"
    },
    "max_score" : 1.0296195,
    "hits" : [
      {
        "_index" : "notelab",
        "_type" : "temperature_topic",
        "_id" : "3",
        "_score" : 1.0296195,
        "_source" : {
          "id" : "rooster",
          "temperature" : 65
        }
      }
    ]
  }
}

```

## (c)

```bash
curl -XGET "http://$SERVER_IP:32200/notelab/_search?pretty" -H 'Content-Type: application/json' -d '{"_source":"temperature","query":{"match_all":{}}}'
```

Output :

```

{
  "took" : 5,
  "timed_out" : false,
  "_shards" : {
    "total" : 1,
    "successful" : 1,
    "skipped" : 0,
    "failed" : 0
  },
  "hits" : {
    "total" : {
      "value" : 3,
      "relation" : "eq"
    },
    "max_score" : 1.0,
    "hits" : [
      {
        "_index" : "notelab",
        "_type" : "temperature_topic",
        "_id" : "1",
        "_score" : 1.0,
        "_source" : {
          "temperature" : 22
        }
      },
      {
        "_index" : "notelab",
        "_type" : "temperature_topic",
        "_id" : "2",
        "_score" : 1.0,
        "_source" : {
          "temperature" : 55
        }
      },
      {
        "_index" : "notelab",
        "_type" : "temperature_topic",
        "_id" : "3",
        "_score" : 1.0,
        "_source" : {
          "temperature" : 65
        }
      }
    ]
  }
}

```

# Assignment 3

```python
import requests, json, time
import logging
    

def query(url, method, payload=None):
    try:
        res = requests.Response()
        if method == "GET":
            res = requests.get(url)
        if method == "POST":
            res = requests.post(
            url,
            data=json.dumps(payload),
            headers={"content-type": "application/json"},
            )
        if method == "PUT":
            res = requests.put(
            url,
            data=json.dumps(payload),
            headers={"content-type": "application/json"},
            )
        if method == "DELETE":
            res = requests.delete(url)
        if res.content is not None:
            logging.debug(
                "HTTP - [" + method + "][" + str(res.status_code) +"][" + url + "]"
            )
            return json.loads(res.content.decode("utf8"))
    except:
        logging.error("HTTP - " + method + " - Connection error!")


if __name__ == "__main__" :
    logging.basicConfig(
        format="%(asctime)s | %(name)s | %(levelname)s | %(message)s",
        level=logging.DEBUG,
    )
    root_url = "http://172.20.10.13:32200/"
    index_es = "notelab"
    for i in range(1,6):
        query(
            url=root_url + index_es + f"/temperature_topic/{i}",
            method="POST",
            payload={"id": f"tester{i}", "temperature": 23+i},
        )
        time.sleep(1)
    for i in range(1,6):
        query(
            url=root_url + index_es + f"/temperature_topic/{i}",
            method="PUT",
            payload={"id": f"tester{i}" ,"temperature": 15+i},
        )
        time.sleep(1)
    query(url=root_url + index_es + "/" + "_search?pretty", method="GET"
                , payload = {"query":{"match_all":{}}})
    time.sleep(1)
    query(url=root_url + index_es, method="DELETE")
```

Output :

```
...
2025-02-28 22:08:04,775 | urllib3.connectionpool | DEBUG | Starting new HTTP connection (1): 172.20.10.13:32200
2025-02-28 22:08:04,807 | root | ERROR | HTTP - POST - Connection error!
2025-02-28 22:08:05,815 | urllib3.connectionpool | DEBUG | Starting new HTTP connection (1): 172.20.10.13:32200
2025-02-28 22:08:06,130 | urllib3.connectionpool | DEBUG | http://172.20.10.13:32200 "PUT /notelab/temperature_topic/1 HTTP/1.1" 200 150
2025-02-28 22:08:06,133 | root | DEBUG | HTTP - [PUT][200][http://172.20.10.13:32200/notelab/temperature_topic/1]
2025-02-28 22:08:07,142 | urllib3.connectionpool | DEBUG | Starting new HTTP connection (1): 172.20.10.13:32200
2025-02-28 22:08:07,446 | urllib3.connectionpool | DEBUG | http://172.20.10.13:32200 "PUT /notelab/temperature_topic/2 HTTP/1.1" 200 150
2025-02-28 22:08:07,450 | root | DEBUG | HTTP - [PUT][200][http://172.20.10.13:32200/notelab/temperature_topic/2]
2025-02-28 22:08:08,459 | urllib3.connectionpool | DEBUG | Starting new HTTP connection (1): 172.20.10.13:32200
2025-02-28 22:08:08,636 | urllib3.connectionpool | DEBUG | http://172.20.10.13:32200 "PUT /notelab/temperature_topic/3 HTTP/1.1" 200 150
2025-02-28 22:08:08,639 | root | DEBUG | HTTP - [PUT][200][http://172.20.10.13:32200/notelab/temperature_topic/3]
2025-02-28 22:08:09,647 | urllib3.connectionpool | DEBUG | Starting new HTTP connection (1): 1
72.20.10.13:32200
2025-02-28 22:08:09,938 | urllib3.connectionpool | DEBUG | http://172.20.10.13:32200 "PUT /not
elab/temperature_topic/4 HTTP/1.1" 200 150
2025-02-28 22:08:09,941 | root | DEBUG | HTTP - [PUT][200][http://172.20.10.13:32200/notelab/t
emperature_topic/4]
2025-02-28 22:08:10,950 | urllib3.connectionpool | DEBUG | Starting new HTTP connection (1): 1
72.20.10.13:32200
2025-02-28 22:08:11,228 | urllib3.connectionpool | DEBUG | http://172.20.10.13:32200 "PUT /not
elab/temperature_topic/5 HTTP/1.1" 200 150
2025-02-28 22:08:11,232 | root | DEBUG | HTTP - [PUT][200][http://172.20.10.13:32200/notelab/t
emperature_topic/5]
2025-02-28 22:08:12,240 | urllib3.connectionpool | DEBUG | Starting new HTTP connection (1): 1
72.20.10.13:32200
2025-02-28 22:08:12,389 | urllib3.connectionpool | DEBUG | http://172.20.10.13:32200 "GET /not
elab/_search?pretty HTTP/1.1" 200 303
2025-02-28 22:08:12,392 | root | DEBUG | HTTP - [GET][200][http://172.20.10.13:32200/notelab/_
search?pretty]
2025-02-28 22:08:13,401 | urllib3.connectionpool | DEBUG | Starting new HTTP connection (1): 1
72.20.10.13:32200
2025-02-28 22:08:14,113 | urllib3.connectionpool | DEBUG | http://172.20.10.13:32200 "DELETE /
notelab HTTP/1.1" 200 47
2025-02-28 22:08:14,116 | root | DEBUG | HTTP - [DELETE][200][http://172.20.10.13:32200/notela
b]
```





