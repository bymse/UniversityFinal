const {parentPort} = require("worker_threads");
const myModule = require("./static/build/UniversityFinal.js");
const {calculate} = require("./static/client.js");

myModule().then(instance => {
  parentPort.on('message', message => {
    handleMessage(message);
  })
});

function handleMessage(instance, command) {
  const myArray = new Int32Array(instance.wasmMemory.buffer, 0, command.type.length)
  for (let i = 0; i < command.type.length; i++) {
    myArray[i] = command.type.charCodeAt(i);
  }

  instance._handle_command(myArray, myArray.length);
}
