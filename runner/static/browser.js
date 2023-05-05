import {initClient} from './client.js';
myModule().then((instance) => {
  const ws = new WebSocket('wss://unvf.bymse.me');
  initClient(ws, instance);
});

function onCommand(instance, event) {
  const command = JSON.parse(event.data);
  const myArray = new Int32Array(instance.wasmMemory.buffer, 0, command.type.length)
  for (let i = 0; i < command.type.length; i++) {
    myArray[i] = command.type.charCodeAt(i);
  }
  instance._handle_command(myArray, myArray.length);
}