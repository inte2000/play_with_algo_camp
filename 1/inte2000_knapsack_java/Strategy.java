import java.util.*;

abstract class Strategy 
{
    private String _name;
    
    Strategy(String name) {
        _name = name;
    }    
    
    String GetName() {
        return _name;
    }
    
    abstract int Choose(PackObject[] objs, int c);
    

}

