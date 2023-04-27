package main

import (
	_ "bytes"
	"fmt"
	"math/rand"
	_ "os/exec"
	"time"

	"github.com/snksoft/crc"
	s "go.bug.st/serial"
)

type BoardPOST struct {
	DataStart string
	Data      []float32
}

func main() {

	temp := rand.Float32()*5.0 + 5.0
	tds := 200.0 + rand.Float32()*20
	params := crc.Parameters{
		Width:      8,
		Polynomial: 0x07,
		Init:       0x00,
		ReflectIn:  false,
		ReflectOut: false,
		FinalXor:   0x00,
	}
	mode := s.Mode{
		BaudRate: 115200,
		DataBits: 8,
		Parity:   s.NoParity,
		StopBits: s.OneStopBit,
	}
	// socat := exec.Command("socat -d -d pty,link=/tmp/vserial1,raw,echo=0 pty,link=/tmp/vserial2,raw,echo=0 &")
	// socat.Run()

	port, err := s.Open("/tmp/vserial1", &mode)
	if err != nil {
		panic(err)
	}
	defer port.Close()

	for i := 0; i < 20; i++ {
		temp += rand.Float32() - 0.5
		tds += 2*rand.Float32() - 1
		bp := BoardPOST{
			DataStart: "X",
			Data:      []float32{temp, tds, temp + 1.0, tds + 2.0, tds * 0.8, temp*1.3 + 2.0},
		}

		buffer := []byte(fmt.Sprintf("%s %d %d %d %d %d %d", bp.DataStart, int32(bp.Data[0]),
			int32(bp.Data[1]), int32(bp.Data[2]), int32(bp.Data[3]),
			int32(bp.Data[4]), int32(bp.Data[5])))
		crc_code := crc.CalculateCRC(&params, buffer)
		buffer = []byte(fmt.Sprintf("%v 0x%02x\r\n", string(buffer), crc_code))
		fmt.Print("Sending data: " + string(buffer))
		port.Write(buffer)

		time.Sleep(2 * time.Second)

	}

}
