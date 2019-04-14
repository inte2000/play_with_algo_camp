
import java.util.*;
import java.io.*;



public class Main {

 	public static void main(String[] args) {
        PackObject[] _objs = { new PackObject(35, 10, 0), new PackObject(30, 40, 0), 
                               new PackObject(60, 30, 0), new PackObject(50, 50, 0), 
                               new PackObject(40, 35, 0), new PackObject(10, 40, 0), 
                               new PackObject(25, 30, 0) };

		Backpack bp = new Backpack(_objs, 150);
        //Strategy stAlgo = new MaxPriceStrategy();
        Strategy stAlgo = new MinWeightStrategy();
        //Strategy stAlgo = new PriceDensityStrategy();
        System.out.println("Using " + stAlgo.GetName() + ": ");
        bp.GreedyAlgo(stAlgo);            
        bp.PrintResult();
        
        
	}
    
}
