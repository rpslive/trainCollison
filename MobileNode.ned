package train;

simple MobileNode
{
    parameters:
        @display("i=abstract/person");
        double timeStep @unit("s") = default(0.1s); // the time granularity of movement calculation
        int trailLength = default(600);	// the length of the trail in time steps showing the past movement of the node. 0 disables the trail
        string color = default(""); // the color of the trail and range indicator in hex BBGGRR format or "" for random color
        string modelURL = default(""); // the URL of the 3D model (COLLADA file format) to be used for the node
        double modelScale = default(1.0); // allows scaling of the used model
        bool showTxRange = default(true);  // whether to show the transmission range around the nodes
        double speed @unit("mps") = default(10mps);  // the speed of the mobile nodes
        double startX @unit("m") = default(0m); // the starting coordinates in meter
        double startY @unit("m") = default(0m); // the starting coordinates in meter
        double txRange @unit("m") = default(200m);  // the transmission range of the mobile node's radio
}

