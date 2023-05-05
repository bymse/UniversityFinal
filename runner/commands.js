import {writeFile} from "fs/promises";  
export function handleCommand(data, onSend, onClose) {
  const command = JSON.parse(data);
  const {type} = command;
  switch (type) {
    case "getArgs":
      handleGetArgs(onSend, onClose);
      break;
    case "result":
      result(command);
      handleGetArgs(onSend, onClose);
      break;
  }
}



const start = 1_900_000_000;
const finish = 1_910_000_000
const shift = 1000;
let lastIteration = start;

const iterations = new Map();  
  
function handleGetArgs(onSend, onClose) {
  if (lastIteration > finish) {
    console.log('completed')
    onClose();
    return;
  }
  iterations.set(lastIteration, {start: new Date()});
  const data = {iteration: lastIteration, args: {from: lastIteration, to: lastIteration + shift}};
  lastIteration += shift;
  onSend(JSON.stringify(data));
}

function result(command) {
  const {result, iteration} = command;
  const {start} = iterations.get(iteration);
  const end = new Date();
  const row = `${iteration}+${shift},${start.toISOString()},${end.toISOString()}\n`
  writeFile("results.csv", row, {flag: "a"}); 
}