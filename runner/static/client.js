function calculate(instance, data) {
  const {args: {from, to}} = data;
  const start = new Date();
  const resultPointer = instance._calculate(from, to);
  const end = new Date();
  const output = new Int32Array(instance.wasmMemory.buffer, resultPointer, 2);
  
  //console.log('calculate', from, to, 'in', end - start, 'ms', 'size', output[0]);
  return {result: new Int32Array(instance.wasmMemory.buffer, output[1], output[0]), resultPointer};
}

module.exports = {
  initClient(ws, instance) {
    ws.onopen = () => {
      ws.send(JSON.stringify({type: "getArgs"}));
    };
    ws.onmessage = (event) => {
      const data = JSON.parse(event.data);
      const {iteration} = data;
      const {result, resultPointer} = calculate(instance, data)
      ws.send(JSON.stringify({type: "result", result, iteration}));
      instance._free_mem(resultPointer);
    }
    ws.onclose = () => {
      console.log('Connection closed');
    }
  },
  calculate
}