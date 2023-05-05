import {WebSocketServer} from 'ws';

export function initializeWsServer(server) {
  return new WebSocketServer({server});
}