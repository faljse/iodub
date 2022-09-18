const fs = require('fs');
const yaml = require('js-yaml');

try {
    let fileContents = fs.readFileSync('./config.yaml', 'utf8');
    let data = yaml.load(fileContents);
    let code="";
    let header="";


    code+=`const uint8_t buttons[${data.Buttons.length*5+1}] PROGMEM = {\n`;
    for(let i=0;i<data.Buttons.length;i++) {
        let b=data.Buttons[i];
        code+=b.pin+", "+b.aidx;
        if(i<data.Buttons.length-1)
            code+=", "; 
    }  
    code+="};\n";
    header+=`extern const uint8_t buttons[${data.Buttons.length*5+1}] PROGMEM;\n`

    code+=`const uint8_t relays[${data.Relays.length*2+1}] PROGMEM = {\n`;
    for(let i=0;i<data.Relays.length;i++) {
        let b=data.Relays[i];
        code+=b.id+", "+b.pin;
        if(i<data.Relays.length-1)
            code+=", ";
    }
    code+="};\n";
    header+=`extern const uint8_t relays[${data.Relays.length*2+1}] PROGMEM;\n`


    code+=`const uint8_t dimmers[${data.Dimmers.length*2+1}] PROGMEM = {\n`;
    for(let i=0;i<data.Dimmers.length;i++) {
        let b=data.Dimmers[i];
        code+=b.id+", "+b.ch;
        if(i<data.Dimmers.length-1)
            code+=", ";
    }
    code+="};\n";
    

    code+=`const uint8_t actions[${data.Actions.length*2+1}][10][10] PROGMEM = {\n`; 
    header+=`extern const uint8_t actions[${data.Actions.length*2+1}][10][10] PROGMEM;\n`

    for(let i=0;i<data.Actions.length;i++) {
        code+="{";
        let b=data.Actions[i];
        for(let j=1; j<10;j++) {
            code+="{";
            for(let k=0;k<10;k++) {
                if(b['action'+j] === undefined)
                    b['action'+j]=[];
                if(b['action'+j][k] === undefined)
                    b['action'+j][k]=0;
                code+=b['action'+j][k] +","
            }
            code = code.slice(0, -1);  
            code+="},"
        }
        code = code.slice(0, -1); 
        code+="},";
    }
    code = code.slice(0, -1); 
    code+="};\n";
    console.log("--")
    console.log(code);
    console.log("--")
    console.log(header);


} catch (e) {
    console.log(e);
}