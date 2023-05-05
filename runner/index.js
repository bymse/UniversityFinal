import {Worker} from "worker_threads";
import "./httpServer.js"
import {getHttpServer} from "./httpServer.js";
import {initializeWsServer} from "./webSocketsServer.js";

const worker = new Worker("./wasiWorker.cjs", {workerData: {}});
const server = getHttpServer(worker);
const ws = initializeWsServer(server);

ws.on('connection', (socket) => {
  socket.on('message', (message) => {
    worker.postMessage(message)
  });
  socket.on('close', () => {
    console.log('Connection closed');
  });
});

worker.on('message', (message) => {
  ws.clients.forEach(client => client.send(message));
});

server.listen(3000, () => {
  console.log(`Server started on port ${server.address().port}`);
});