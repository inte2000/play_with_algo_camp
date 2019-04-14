import java.util.*;
import java.io.*;


class Backpack {
    private PackObject[] _objs = null;
    private int _totalC = 0;
    
	public Backpack(PackObject[] objs, int c) {
		super();
        _objs = objs;
        _totalC = c;
	}

    public void GreedyAlgo(Strategy fs) {
        int idx;
        int ntc = 0;

        //spFunc 每次选最符合策略的那个物品，选后再检查
        while((idx = fs.Choose(_objs, _totalC - ntc)) != -1)
        {
            //所选物品是否满足背包承重要求？
            if((ntc + _objs[idx].weight) <= _totalC)
            {
                _objs[idx].status = 1;
                ntc += _objs[idx].weight;
            }
            else
            {
                //不能选这个物品了，做个标记后重新选
                _objs[idx].status = 2; 
            }
        }
    }

    public void PrintResult() {
        int totalW = 0;
        int totalP = 0;
        
        for(int i = 0; i < _objs.length; i++) {
            if(_objs[i].status == 1) {
                totalW += _objs[i].weight;
                totalP += _objs[i].price;
                System.out.println("object " + (i + 1) + ": weight=" + _objs[i].weight + ", price=" + _objs[i].price);
            }
        }
        System.out.println("total weight : " + totalW + ", total price : " + totalP);
    }


}
