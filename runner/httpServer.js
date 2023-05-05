import express from "express";
import * as http from "http";

const app = express();

export function getHttpServer(worker) {
  app.use((req, res, next) => {
    res.setHeader('Cross-Origin-Opener-Policy', 'same-origin')
    res.setHeader('Cross-Origin-Embedder-Policy', 'require-corp')
    next();
  });
  app.get('/', (req, res) => {
    res.sendFile('index.html', {root: "."});
  });

  app.post('/api/task/create', (req, res) => {
    worker.postMessage({type: "TaskCreate", data: req.body});
  });

  app.get('/api/task/status', (req, res) => {
    worker.postMessage({type: "TaskStatus", data: req.body});
  });

  app.post('/api/task/cancel', (req, res) => {
    worker.postMessage({type: "TaskCancel", data: req.body});
  });

  app.get('/api/task/results', (req, res) => {
    worker.postMessage({type: "TaskResults", data: req.body});
  });

  app.post('/api/cluster/connect', (req, res) => {
    worker.postMessage({type: "NodeConnectionToCluster", data: req.body});
  });

  app.listen(3000, () => {
    console.log('Server started on port 3000');
  });


  app.use('/static', express.static('static'));
  return http.createServer(app);
}