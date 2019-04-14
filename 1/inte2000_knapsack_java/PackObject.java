class PackObject
{
    public int weight;
    public int price;
    public int status;  //0:未选中；1:已选中；2:已经不可选

    public PackObject(int weight, int price, int status) {
        this.weight = weight;
        this.price = price;
        this.status = status;
    }
    public PackObject(PackObject w) {
        this.weight = w.weight;
        this.price = w.price;
        this.status = w.status;
    }
}