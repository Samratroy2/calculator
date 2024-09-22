function appendToInput(value) {
    document.getElementById('input').value += value;
}

function calculate() {
    const input = document.getElementById('input').value;
    
    // Replace ^ with ** for power calculation in eval
    const formattedInput = input.replace(/\^/g, '**');
    
    try {
        const result = eval(formattedInput);
        document.getElementById('input').value = result;
    } catch (error) {
        alert("Invalid Expression");
    }
}

function clearInput() {
    document.getElementById('input').value = '';
}

function backspace() {
    const input = document.getElementById('input');
    input.value = input.value.slice(0, -1);
}

// Function to handle keyboard input
document.addEventListener('keydown', function(event) {
    const key = event.key;

    if (key.match(/[0-9+\-*/().]/)) {
        appendToInput(key);
    } else if (key === 'Enter') {
        calculate();
    } else if (key === 'Backspace') {
        backspace();
    } else if (key === 'Escape') {
        clearInput();
    }
});
