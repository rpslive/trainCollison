//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package train;
//
// TODO documentation
//

simple TSU
{
    gates:
        input in0;
        input in1;
        output out0;
        output out1;
}

//
// TODO documentation
//
network Network

{
    @display("bgb=937,283");

    //parameters:
    //   @display("bgb=2000,2000;bgi=background/terrain,s");
    double playgroundWidth @unit("m") = default(937m);  // the E-W size of playground
    double playgroundHeight @unit("m") = default(283m); // the N-S size of playground

    types:
    submodules:
        
        chanCtrl: ChannelController {
            @display("p=20,30");
        }
        train: MobileNode {

            @display("p=50,98;i=device/train");
        }
        TSU1: TSU {
            @display("p=63,203;i=device/antennatower;is=l");
        }
        TSU2: TSU {
            @display("p=336,203;i=device/antennatower;is=l");
        }
        TSU3: TSU {
            @display("p=590,203;i=device/antennatower;is=l");
        }
        TSU4: TSU {
            @display("p=843,203;i=device/antennatower;is=l");
        }

    connections:
        TSU1.out0 --> TSU1.in0;
        TSU1.out1 --> TSU2.in0;
        TSU2.out0 --> TSU1.in1;
        TSU2.out1 --> TSU3.in0;
        TSU3.out0 --> TSU2.in1;
        TSU3.out1 --> TSU4.in0;
        TSU4.out0 --> TSU3.in1;
        TSU4.out1 --> TSU4.in1;


}
