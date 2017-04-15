import java.io._

object Main {
  def main(args: Array[String]): Unit = {
    val fileLists = new File(args(0)).listFiles

    val wcList = for (file <- fileLists if file.getName.startsWith("temp_0")) yield {
      wordCount(getFileLines(file))
    }

    val result = wcList.reduce((map1, map2) => {
        map2.foldLeft(map1)((map, pair) => {
          val value = map.getOrElse(pair._1, 0)
          map.updated(pair._1, value + pair._2)
        })
      }
    )

    val intermediateResult = fileLists.filter(file => file.getName.startsWith("temp_2")).map(file => wordCount(getFileLines(file)))
 
    val result2 = intermediateResult(0)  

    println(result.foldLeft(true)((bool, pair) => bool && result2(pair._1) == pair._2))
  }
  
  def getFileLines(file: File) = 
    scala.io.Source.fromFile(file).getLines().toList
  
  def wordCount(fileLines: List[String]) = {
    val map = Map[String, Int]() 
    def nested(list: List[String], map: Map[String, Int]): Map[String, Int] = 
    list match {
      case Nil => map
      case xs :: tl => {
        val value = map.getOrElse(xs, 0)
        nested(tl, map.updated(xs, value + 1))
      }
    }
    nested(fileLines, map)
  }
}
